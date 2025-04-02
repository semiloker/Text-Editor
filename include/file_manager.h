#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <cstdint>
#include <windows.h>

#define text_buffer 50000

class FileManager
{
public:
    void SaveData(LPCSTR path, HWND hEditText);
    void LoadData(LPCSTR path, HWND hEditText);
    void OpenParams(HWND hwnd);

    wchar_t buffer[text_buffer];
    char file_name[150];
    OPENFILENAME ofn;
};

#endif