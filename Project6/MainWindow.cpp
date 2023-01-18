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

void MainWindow::fatalError(LPCWSTR errorString) {
    MessageBox(NULL, errorString, L"Fatal Error", MB_OK);
}
std::string rgbToHex(int r, int g, int b, bool with_head)
{
    std::stringstream ss;
    if (with_head)
        ss << "0x";
    ss << std::hex << (r << 16 | g << 8 | b);
    return ss.str();
}
LRESULT CALLBACK MainWindow::WndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    LRESULT result;
    MainWindow* mainWindow = reinterpret_cast<MainWindow*>(lParam);
    switch (message) {
    case WM_CLOSE:
    {
        mainWindow->_windowState = WindowState::EXIT;
    }
    case WM_EXITSIZEMOVE:
    {
        mainWindow->drawScreen();
    }
    default:
    {
        result = DefWindowProc(window, message, wParam, lParam);
    }
    }
    return 0;
}
MainWindow::MainWindow() 
{
	_screenWidth = 1688;
	_screenHeight = 1050;
	_windowState = WindowState::RUN;
	_mesh = Mesh(std::list<Vector3> {
		Vector3(10, 0, 10),
		Vector3(10, 0, 0),
		Vector3(10, 10, 0),
		Vector3(10, 10, 10),
		Vector3(0, 0, 10),
		Vector3(0, 0, 0),
		Vector3(0, 10, 0),
		Vector3(0, 10, 10)
	},
	std::list<int>
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
	initSystems(hInstance, nShowCmd);
	mainLoop();
}

void MainWindow::initSystems(HINSTANCE hInstance, int nShowCmd)
{
    _windowclass.lpfnWndProc = &MainWindow::WndProc;
    _windowclass.hInstance = hInstance;
    _windowclass.lpszClassName = _classname;
    RegisterClass(&_windowclass);
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
        reinterpret_cast<LPVOID>(this)
    );
    if (!_window) {
        fatalError(L"Failed to Create Window."); 
    }
    _windowState;
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
}

void MainWindow::processInput() {
    MSG msg;
    while (PeekMessage(&msg, _window, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void MainWindow::drawScreen(){
    VirtualFree(memory,0, MEM_RELEASE);
    RECT rect;
    GetClientRect(_window, &rect);
    _screenWidth = rect.right - rect.left;
    _screenHeight = rect.bottom - rect.top;
    memory = VirtualAlloc(0,
        _screenWidth * _screenHeight * 4,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );
    std::uint32_t* pixel = (std::uint32_t*)memory;
    for (int pn = 0; pn < _screenWidth * _screenHeight; ++pn) {
        int r = abs(sin((double)pn)) * 255;
        int g = 255;
        int b = 0;
        *pixel++ = std::stoul(rgbToHex(r, g, b, true), nullptr, 16);
    }
    std::uint32_t red = 0xFF0000;
    _bitmapInfo.bmiHeader.biSize = sizeof(_bitmapInfo.bmiHeader);
    _bitmapInfo.bmiHeader.biWidth = _screenWidth;
    _bitmapInfo.bmiHeader.biHeight = _screenHeight;
    _bitmapInfo.bmiHeader.biPlanes = 1;
    _bitmapInfo.bmiHeader.biBitCount = 32;
    _bitmapInfo.bmiHeader.biCompression = BI_RGB;
}