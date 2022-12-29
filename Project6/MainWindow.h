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
	void fatalError(std::string errorString);

private:
	void initSystems(HINSTANCE hInstance, int nShowCmd);
	void mainLoop();
	void processInput();
	WNDCLASSEX _window;
	int _screenWidth;
	int _screenHeight;
	WindowState _gameState;
	Vector3 _v3;
	Mesh _mesh;
	Color color;
	RenderObject _ro;
};

