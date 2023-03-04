#define UNICODE
#define _UNICODE

#include <fcntl.h>
#include <io.h>
#include "MainWindow.h"
#include <iostream>
#include <sstream>
#include <cstdint>
#include <list>
#include <wingdi.h>
#include <iomanip>

MainWindow* mW;

void MainWindow::fatalError(LPCWSTR errorString) {
    MessageBox(NULL, errorString, L"Fatal Error", MB_OK);
}
int MainWindow::CoordsToBitMapIndex(Vector2 coords, int width, int height) {
    if (coords.x > width || coords.y > height) { return 0; }
    int index = coords.y * width + coords.x;
    return index;
}
Vector2 MainWindow::BitMapIndexToCoords(int index, int width, int height) {
    Vector2 coords = Vector2(0,0);
    if (index > width * height || width == 0 || height == 0) { return coords; }
    coords.y = floor(index / width);
    coords.x = floor(index % width);
}
LRESULT CALLBACK MainWindow::WndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    LRESULT result;
    switch (message) {
    case WM_CLOSE:
    {
        mW->_windowState = WindowState::EXIT;
        return 0;
    }
    case WM_EXITSIZEMOVE:
    {
        mW->drawScreen();
        return 0;
    }
    case WM_SIZING: {
        RECT* rect = (RECT*)lParam;
        int width = rect->right - rect->left;
        int height = rect->bottom - rect->top;
        if (width < 600) {rect->right = rect->left + 600;}
        if (height < 400) {rect->bottom = rect->top + 400;}

        mW->renderEngine.aspectRatio = width / height;
        mW->_screenWidth = width;
        mW->_screenHeight = height;
        return 0;
    }
    case WM_KEYDOWN: {
        mW->renderEngine.cameraPosition.z++;
        mW->renderEngine.UpdateTransformationMatrix();
        mW->renderEngine.UpdateProjectionMatrix();
        std::cout << mW->renderEngine.cameraPosition.z << std::endl;
    }
    default:
    {
        result = DefWindowProc(window, message, wParam, lParam);
    }
    }
    return result;
}
MainWindow::MainWindow() 
{
	_screenWidth = 720;
	_screenHeight = 480;
	_windowState = WindowState::RUN;
    renderEngine.aspectRatio = (double)_screenWidth / _screenHeight;

    renderEngine.UpdateTransformationMatrix();
    renderEngine.UpdateProjectionMatrix();
	_mesh = Mesh(std::vector<Vector3> {
		Vector3(200, 0, 400),
		Vector3(200, 0, 300),
		Vector3(200, 100, 300),
		Vector3(200, 100, 400),
		Vector3(100, 0, 400),
		Vector3(100, 0, 300),
		Vector3(100, 100, 300),
		Vector3(100, 100, 400)
	},
	std::vector<int>
	{
		4, 0, 3, 4, 3, 7, 0, 1, 2, 0, 2, 3, 1, 5, 6, 1, 6, 2, 5, 4, 7, 5, 7, 6, 7, 3, 2, 7, 2, 6, 0, 5, 1, 0, 4, 5
	});
	color = Color(ColorMode::RGB1, 0.5, 0.5, 0.5);
}
MainWindow::~MainWindow() 
{
}

void MainWindow::run(HINSTANCE hInstance, int nShowCmd)
{
    mW = this;
	initSystems(hInstance, nShowCmd);
	mainLoop();
}

void MainWindow::initSystems(HINSTANCE hInstance, int nShowCmd)
{
    _windowclass.lpfnWndProc = &MainWindow::WndProc;
    _windowclass.hInstance = hInstance;
    _windowclass.lpszClassName = _classname;
    if (!RegisterClass(&_windowclass)) { fatalError(L"Failed to register the window class"); }
    _window = CreateWindowEx(
        0,
        _classname,
        _windowname,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0,
        0,
        _screenWidth,
        _screenHeight,
        0,
        0,
        hInstance,
        0
    );
    if (!_window) {
       fatalError(L"Failed to Create Window."); 
    }
    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    std::cout << "\\|/ " << GetCommandLineA() << " - Debug Console \\|/" << std::endl;
}
void MainWindow::mainLoop()
{
    drawScreen();
    HDC hdc = GetDC(_window);
    while (_windowState != WindowState::EXIT)
    {
        drawScreen();
        processInput();
        StretchDIBits(
            hdc,
            0,
            0,
            _screenWidth,
            _screenHeight,
            0,
            0,
            _screenWidth,
            _screenHeight,
            memory,
            &_bitmapInfo,
            DIB_RGB_COLORS,
            SRCCOPY
        );

    }
    FreeConsole();
    ReleaseDC(_window, hdc);

}

void MainWindow::processInput() {
    MSG msg;
    while (PeekMessage(&msg, _window, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void MainWindow::drawScreen(){
    if (memory != nullptr)
    {
        VirtualFree(memory, 0, MEM_RELEASE);
    }
    RECT rect;
    GetClientRect(_window, &rect);
    _screenWidth = rect.right - rect.left;
    _screenHeight = rect.bottom - rect.top;
    memory = VirtualAlloc(0,
        _screenWidth * _screenHeight * 4,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );
    _mesh = Rotation::rotMesh(_mesh, Vector3(0.1,0.1,0.1), Mesh::calculateCenter(_mesh));
    std::vector<std::vector<Vector2>> ros = RenderEngine::ConvertMeshToRenderObjects(_mesh, renderEngine, _screenWidth, _screenHeight);

    for (std::vector<Vector2> ro : ros) {
        plotTriangle(ro[0], ro[1], ro[2], Color(ColorMode::RGB1,255,0,0), false);
    }
    _bitmapInfo.bmiHeader.biSize = sizeof(_bitmapInfo.bmiHeader);
    _bitmapInfo.bmiHeader.biWidth = _screenWidth;
    _bitmapInfo.bmiHeader.biHeight = _screenHeight;
    _bitmapInfo.bmiHeader.biPlanes = 1;
    _bitmapInfo.bmiHeader.biBitCount = 32;
    _bitmapInfo.bmiHeader.biCompression = BI_RGB;
}
void MainWindow::plotLine(Vector2 p1, Vector2 p2, Color color) {
    std::uint32_t* pixel = (std::uint32_t*)memory;
    if (!pixel) {
        return;
    }
    int x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
    if (x1 < 0) x1 = 0;
    if (x1 >= _screenWidth) x1 = _screenWidth - 1;
    if (y1 < 0) y1 = 0;
    if (y1 >= _screenHeight) y1 = _screenHeight - 1;
    if (x2 < 0) x2 = 0;
    if (x2 >= _screenWidth) x2 = _screenWidth - 1;
    if (y2 < 0) y2 = 0;
    if (y2 >= _screenHeight) y2 = _screenHeight - 1;
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1, sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    while (true) {
        Vector2 coords = Vector2(x1, y1);
        int index = CoordsToBitMapIndex(coords, _screenWidth, _screenHeight);
        float intensity = abs(err - dx + dy) / (float)(dx + dy);
        pixel[index] = Color::colorClassToHex(color);
        if (x1 == x2 && y1 == y2) { break; };
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}
void MainWindow::plotTriangle(Vector2 p1, Vector2 p2, Vector2 p3, Color c, bool fill) {
    plotLine(p1, p2, c);
    plotLine(p2, p3, c);
    plotLine(p3, p1, c);
}
