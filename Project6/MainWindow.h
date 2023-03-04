#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Mesh.h"
#include "Color.h"
#include "RenderEngine.h"
#include "Matrix.h"
#include "Rotation.h"
#include <Windows.h>
enum class WindowState {RUN, EXIT};

class MainWindow
{
public:
	MainWindow();
	~MainWindow();
	void run(HINSTANCE hInstance, int nShowCmd);
	void fatalError(LPCWSTR errorString);
	LPCWSTR _classname = L"WindowClass";
	LPCWSTR _windowname = L"Window";
	int _screenWidth;
	int _screenHeight;
	static int CoordsToBitMapIndex(Vector2 coords, int width, int height);
	static Vector2 BitMapIndexToCoords(int index, int width, int height);
	void plotLine(Vector2 p1, Vector2 p2, Color color);
	void plotTriangle(Vector2 p1, Vector2 p2, Vector2 p3, Color c, bool fill);
	
private:
	void initSystems(HINSTANCE hInstance, int nShowCmd);
	void mainLoop();
	void processInput();
	void drawScreen();
	void* memory;
	BITMAPINFO _bitmapInfo;
	static LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
	WNDCLASS _windowclass;
	HWND _window;
	WindowState _windowState;
	RenderEngine renderEngine;
	Mesh _mesh;
	Color color;
};

