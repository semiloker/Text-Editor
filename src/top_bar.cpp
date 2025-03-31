#include "../include/top_bar.h"

TopBar::TopBar()
{
    file_manager = new FileManager();
}

void TopBar::CreateMenuBar(HWND hwnd)
{
    HMENU hMenu = CreateMenu();
    HMENU hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, MENU_FILE_LOAD, "Open");
    AppendMenu(hSubMenu, MF_STRING, MENU_FILE_SAVE, "Save");
    AppendMenu(hSubMenu, MF_SEPARATOR, NULL, "");
    AppendMenu(hSubMenu, MF_STRING, MENU_EXIT, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Menu");
    SetMenu(hwnd, hMenu);
}

void TopBar::MenuOnCommand(HWND hwnd, WPARAM wParam, HWND hEditText)
{
    switch (LOWORD(wParam)) 
    {
    case MENU_FILE_LOAD:
        if (GetOpenFileName(&file_manager->ofn))
            file_manager->LoadData(file_manager->file_name, hEditText);
        break;
    case MENU_FILE_SAVE:
        if (GetSaveFileName(&file_manager->ofn))
            file_manager->SaveData(file_manager->file_name, hEditText);
        break;
    case MENU_EXIT:
        PostQuitMessage(0);
        break;
    }
}