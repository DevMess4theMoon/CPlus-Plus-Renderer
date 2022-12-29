#include "MainWindow.h"
#include <iostream>
#include <string>
#include <list>
void MainWindow::fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;

}

MainWindow::MainWindow() 
{
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = WindowState::RUN;
	_v3 = Vector3(10,5,10);
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
    _window.cbSize = sizeof(WNDCLASSEX);
    _window.style = CS_HREDRAW | CS_VREDRAW;
    _window.lpfnWndProc = DefWindowProc;
    _window.cbClsExtra = 0;
    _window.cbWndExtra = 0;
    _window.hInstance = hInstance;
    _window.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    _window.hCursor = LoadCursor(NULL, IDC_ARROW);
    _window.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    _window.lpszMenuName = NULL;
    _window.lpszClassName = "MyWindowClass";
    _window.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    if (!RegisterClassEx(&_window)) {fatalError("Failed to register the window class");}
    // Create the window
    _Post_ _Notnull_ HWND hwnd = CreateWindowEx(
        0,
        "MyWindowClass",
        "My Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        640, 480,
        NULL, NULL,
        hInstance,
        NULL
    );
    if (!hwnd) {fatalError("Failed to create the window");}
    // Show the window and paint it for the first time
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);
}

void MainWindow::mainLoop() {
	while (_gameState != WindowState::EXIT) {
        processInput();
	}
}

void MainWindow::processInput() {
    MSG msg;
    if(GetMessage(&msg, NULL, 0, 0))
    {
        if (msg.message == WM_QUIT) {
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}