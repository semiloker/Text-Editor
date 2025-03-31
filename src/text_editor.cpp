#include "../include/text_editor.h"

void TextEditor::CreateTextEditWindow(HWND hwnd, HINSTANCE hInstance) 
{
    RECT rcClient;
    GetClientRect(hwnd, &rcClient);

    hEditText = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL | ES_AUTOHSCROLL,
        5, 5, rcClient.right - 10, rcClient.bottom - 10, hwnd, NULL, hInstance, NULL);

    if (hEditText) 
    {
        SubclassEditControl();
    }
}

void TextEditor::ResizeWindow(HWND hwnd) 
{
    if (hEditText) 
    {
        RECT rcClient;
        GetClientRect(hwnd, &rcClient);
        MoveWindow(hEditText, 5, 5, rcClient.right - 10, rcClient.bottom - 10, TRUE);
    }
}

WNDPROC TextEditor::oldEditProc = nullptr;

void TextEditor::SubclassEditControl() 
{
    oldEditProc = (WNDPROC)SetWindowLongPtr(hEditText, GWLP_WNDPROC, (LONG_PTR)EditProc);
}

std::stack<std::string> undoStack;

LRESULT CALLBACK TextEditor::EditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    if (msg == WM_KEYDOWN && (GetKeyState(VK_CONTROL) & 0x8000)) 
    {
        if (wParam == 'Z')
        {
            if (!undoStack.empty()) 
            {
                std::string lastState = undoStack.top();
                undoStack.pop();

                SetWindowText(hwnd, lastState.c_str());
                return 0;
            }
        }
        if (wParam == VK_BACK) 
        {
            int start, end;
            SendMessage(hwnd, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

            if (start == end && start > 0) 
            {
                int textLength = GetWindowTextLength(hwnd) + 1;
                char* buffer = new char[textLength];
                GetWindowText(hwnd, buffer, textLength);

                int newPos = start;
                while (newPos > 0 && buffer[newPos - 1] == ' ') newPos--;
                while (newPos > 0 && buffer[newPos - 1] != ' ') newPos--;

                char* currentText = new char[textLength];
                GetWindowText(hwnd, currentText, textLength);
                undoStack.push(std::string(currentText));
                delete[] currentText;

                SendMessage(hwnd, EM_SETSEL, newPos, start);
                SendMessage(hwnd, EM_REPLACESEL, FALSE, (LPARAM)"");

                delete[] buffer;
            }
            return 0;
        }
        else if (wParam == 'A') 
        {
            SendMessage(hwnd, EM_SETSEL, 0, -1);
            return 0;
        }
    }
    return CallWindowProc(oldEditProc, hwnd, msg, wParam, lParam);
}