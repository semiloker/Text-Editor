#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <windows.h>
#include <stack>
#include <iostream>
#include <string>

class TextEditor
{
public:
    void CreateTextEditWindow(HWND hwnd, HINSTANCE hInstance);
    void ResizeWindow(HWND hwnd);
    void SubclassEditControl();

    HWND hEditText;
    
    static WNDPROC oldEditProc;
    static LRESULT CALLBACK EditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif