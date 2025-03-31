#ifndef TOP_BAR_H
#define TOP_BAR_H

#include <Windows.h>
#include "define.h"
#include "file_manager.h"

class TopBar
{
public:
    TopBar();
    ~TopBar() = default;
    void CreateMenuBar(HWND hwnd);
    void MenuOnCommand(HWND hwnd, WPARAM wParam, HWND hEditText);

    FileManager* file_manager;
};

#endif