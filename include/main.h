#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <winuser.h>
#include "../include/define.h"
#include "../include/top_bar.h"
#include "../include/text_editor.h"

class MainWindow
{
public:
    MainWindow(HINSTANCE hInstance);
    ~MainWindow() = default;
    bool Register();
    bool Create(int nCmdShow);
    WPARAM RunMessageLoop();

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    void OnCommand(WPARAM wParam);
    void OnGetMinMaxInfo(LPARAM lParam);
    void OnCreate(HWND hwnd);
    void OnResize();
    void OnKeydown(WPARAM wParam);
    void OnDestroy();

    static const char szClassName[];

    HINSTANCE hInstance;
    HWND hwnd;

    TopBar* top_bar;
    TextEditor* text_editor;
};

#endif