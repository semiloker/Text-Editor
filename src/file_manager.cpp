#include "../include/file_manager.h"

void FileManager::SaveData(LPCSTR path, HWND hEditText)
{
    HANDLE FileToSave = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileToSave == INVALID_HANDLE_VALUE) return;

    int text_length = GetWindowTextLengthW(hEditText) + 1;
    wchar_t* data = new wchar_t[text_length];

    text_length = GetWindowTextW(hEditText, data, text_length);
    
    DWORD bytes;

    WORD bom = 0xFEFF;
    WriteFile(FileToSave, &bom, sizeof(WORD), &bytes, NULL);

    WriteFile(FileToSave, data, text_length * sizeof(wchar_t), &bytes, NULL);

    CloseHandle(FileToSave);
    delete[] data;
}

void FileManager::LoadData(LPCSTR path, HWND hEditText)
{
    HANDLE FileToLoad = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (FileToLoad == INVALID_HANDLE_VALUE) return;

    DWORD bytes;
    ReadFile(FileToLoad, buffer, text_buffer * sizeof(wchar_t), &bytes, NULL);
    
    if (buffer[0] == 0xFEFF)
    {
        SetWindowTextW(hEditText, buffer + 1);
    }
    else
    {
        SetWindowTextW(hEditText, buffer);
    }

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