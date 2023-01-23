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
LRESULT CALLBACK MainWindow::WndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    LRESULT result;
    switch (message) {
    case WM_CLOSE:
    {
        mW->_windowState = WindowState::EXIT;
    }
    case WM_EXITSIZEMOVE:
    {
        mW->drawScreen();
    }
    case WM_SIZE:
    {
        mW->drawScreen();
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
    std::uint32_t* pixel = (std::uint32_t*)memory;
    for (int pn = 0; pn < _screenWidth * _screenHeight; ++pn) {
        *pixel++ = Color::rgbToHex(pn, pn, pn);
    }
    _bitmapInfo.bmiHeader.biSize = sizeof(_bitmapInfo.bmiHeader);
    _bitmapInfo.bmiHeader.biWidth = _screenWidth;
    _bitmapInfo.bmiHeader.biHeight = _screenHeight;
    _bitmapInfo.bmiHeader.biPlanes = 1;
    _bitmapInfo.bmiHeader.biBitCount = 32;
    _bitmapInfo.bmiHeader.biCompression = BI_RGB;
}