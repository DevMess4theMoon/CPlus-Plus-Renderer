#include "mainWindow.h"
#include <windows.h>
#include <WinBase.h>
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
    MainWindow mainWindow;
    mainWindow._classname = L"WindowClass";
    mainWindow._windowname = L"Window";
    mainWindow.run(hInstance, nShowCmd);
    return 0;
}