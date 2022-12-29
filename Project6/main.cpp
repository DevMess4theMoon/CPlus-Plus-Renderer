#include "mainWindow.h"
#include <windows.h>
#include <WinBase.h>
#include <string>
#include <iostream>
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
    MainWindow mainWindow;
    mainWindow.run(hInstance, nShowCmd);
    return 0;
}