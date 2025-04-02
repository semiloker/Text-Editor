#include "../include/file_manager.h"
#include <winnt.h>

void FileManager::SaveData(LPCSTR path, HWND hEditText)
{
    HANDLE FileToSave = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    int text_lenght = GetWindowTextLength(hEditText) + 1;
    wchar_t* data = new wchar_t[text_lenght];

    text_lenght = GetWindowTextW(hEditText, data, text_lenght);
    DWORD bytes;
    WriteFile(FileToSave, data, text_lenght, &bytes, NULL);
    CloseHandle(FileToSave);

    delete[] data;
}

void FileManager::LoadData(LPCSTR path, HWND hEditText)
{
    HANDLE FileToLoad = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD bytes;
    ReadFile(FileToLoad, buffer, text_buffer, &bytes, NULL);

    SetWindowTextW(hEditText, buffer);

    CloseHandle(FileToLoad);
}

void FileManager::OpenParams(HWND hwnd)
{
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = file_name;
    ofn.nMaxFile = sizeof(file_name);
    ofn.lpstrFilter = "*.txt";
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}