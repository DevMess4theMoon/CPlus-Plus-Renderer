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
        return 0;
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
	_screenWidth = 1688;
	_screenHeight = 1050;
	_windowState = WindowState::RUN;
	_mesh = Mesh(std::vector<Vector3> {
		Vector3(200, 100, 200),
		Vector3(200, 100, 100),
		Vector3(200, 200, 100),
		Vector3(200, 200, 200),
		Vector3(100, 100, 200),
		Vector3(100, 100, 100),
		Vector3(100, 200, 100),
		Vector3(100, 200, 200)
	},
	std::vector<int>
	{
		4, 0, 3, 4, 3, 7, 0, 1, 2, 0, 2, 3, 1, 5, 6, 1, 6, 2, 5, 4, 7, 5, 7, 6, 7, 3, 2, 7, 2, 6, 0, 5, 1, 0, 4, 5
	});
	color = Color(ColorMode::RGB1, 0.5, 0.5, 0.5);
    mat = Matrix(3, 1, 
        {{3,4,2}});
    mat2 = Matrix(4, 3,
        { {13,9,7,15}, {8,7,4,6}, {6,4,0,3} });
    mat = mat * mat2;
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
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        hInstance,
        0
    );
    if (!_window) {
       fatalError(L"Failed to Create Window."); 
    }
}
void MainWindow::mainLoop()
{
    drawScreen();
    HDC hdc = GetDC(_window);
    while (_windowState != WindowState::EXIT)
    {
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
    //plotTriangle(Vector2(50, 75), Vector2(100, 50), Vector2(100,150), Color(ColorMode::RGB1, 255,0,255),false);
    std::vector<RenderObject> ros = RenderEngine::ConvertMeshToRenderObjects(_mesh, _screenWidth, _screenHeight);

    for (RenderObject ro : ros) {
        plotTriangle(ro.coordinates[0], ro.coordinates[1], ro.coordinates[2], Color(ColorMode::RGB1,255,0,0), false);
    }
    _bitmapInfo.bmiHeader.biSize = sizeof(_bitmapInfo.bmiHeader);
    _bitmapInfo.bmiHeader.biWidth = _screenWidth;
    _bitmapInfo.bmiHeader.biHeight = _screenHeight;
    _bitmapInfo.bmiHeader.biPlanes = 1;
    _bitmapInfo.bmiHeader.biBitCount = 32;
    _bitmapInfo.bmiHeader.biCompression = BI_RGB;
}
void MainWindow::plotLine(Vector2 p1, Vector2 p2, Color color) {
    int x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1, sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        Vector2 coords = Vector2(x1, y1);
        int index = CoordsToBitMapIndex(coords, _screenWidth, _screenHeight);
        float intensity = abs(err - dx + dy) / (float)(dx + dy);
        std::uint32_t* pixel = (std::uint32_t*)memory;
        if (pixel) {
            pixel[index] = Color::colorClassToHex(Color::interpolate(color, Color(ColorMode::RGB1, 0, 0, 0), intensity));
        }
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
