#pragma once
#include "Vector3.h"
#include "Mesh.h"
#include "Color.h"
#include "RenderObject.h"
#include <Windows.h>
enum class WindowState {RUN, EXIT};

class MainWindow
{
public:
	MainWindow();
	~MainWindow();
	void run(HINSTANCE hInstance, int nShowCmd);
	void fatalError(LPCWSTR errorString);
	std::string decToHex(int n);
	LPCWSTR _classname = L"WindowClass";
	LPCWSTR _windowname = L"Window";
private:
	void initSystems(HINSTANCE hInstance, int nShowCmd);
	void mainLoop();
	void processInput();
	void drawScreen(HWND hwnd);
	void* memory;
	BITMAPINFO _bitmapInfo;
	static LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
	WNDCLASS _windowclass;
	HWND _window;
	WindowState _windowState;
	int _screenWidth;
	int _screenHeight;
	Mesh _mesh;
	Color color;
	RenderObject _ro;
};

