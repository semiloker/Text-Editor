#include "../include/main.h"

const char MainWindow::szClassName[] = "Text Editor";

MainWindow::MainWindow(HINSTANCE hInstance) : hInstance(hInstance), hwnd(NULL) {}

bool MainWindow::Register() 
{
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassEx(&wc) != 0;
}

bool MainWindow::Create(int nCmdShow) 
{
    top_bar = new TopBar();
    text_editor = new TextEditor();

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int windowWidth = 500;
    int windowHeight = 400;
    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE, szClassName, szClassName, WS_OVERLAPPEDWINDOW,
        x, y, windowWidth, windowHeight,
        NULL, NULL, hInstance, this);

    if (!hwnd) 
    {
        MessageBox(NULL, "Could not create a window!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return true;
}

WPARAM MainWindow::RunMessageLoop() {
    MSG Msg;
    while (GetMessage(&Msg, NULL, 0, 0) > 0) 
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK MainWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    MainWindow* pThis = nullptr;
    
    if (msg == WM_NCCREATE) 
    {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (MainWindow*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
    } 
    else 
    {
        pThis = (MainWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (!pThis) 
    {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    switch (msg) 
    {
        case WM_COMMAND:    pThis->OnCommand(wParam); break;
        case WM_GETMINMAXINFO: pThis->OnGetMinMaxInfo(lParam); break;
        case WM_CREATE:     pThis->OnCreate(hwnd); break;
        case WM_SIZE:       pThis->OnResize(); break;
        case WM_CLOSE:      DestroyWindow(hwnd); break;
        case WM_DESTROY:    pThis->OnDestroy(); break;
        default:            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void MainWindow::OnCreate(HWND hwnd)
{
    if (top_bar) 
    {
        top_bar->CreateMenuBar(hwnd);
    }
    
    if (text_editor) 
    {
        text_editor->CreateTextEditWindow(hwnd, hInstance);
    }

    if (top_bar && top_bar->file_manager) 
    {
        top_bar->file_manager->OpenParams(hwnd);
    }
}

void MainWindow::OnCommand(WPARAM wParam)
{
    if (top_bar && text_editor) 
    {
        top_bar->MenuOnCommand(hwnd, wParam, text_editor->hEditText);
    }
}

void MainWindow::OnResize()
{
    if (text_editor) {
        text_editor->ResizeWindow(hwnd);
    }
}

void MainWindow::OnKeydown(WPARAM wParam)
{
    // Обробка перенесена до EditProc
}

void MainWindow::OnGetMinMaxInfo(LPARAM lParam) 
{
    MINMAXINFO* mmi = (MINMAXINFO*)lParam;
    mmi->ptMinTrackSize.x = 350;
    mmi->ptMinTrackSize.y = 350;
}

void MainWindow::OnDestroy() 
{
    if (top_bar) {
        delete top_bar;
        top_bar = nullptr;
    }
    
    if (text_editor) {
        delete text_editor;
        text_editor = nullptr;
    }
    
    PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
    MainWindow mainWindow(hInstance);
    if (!mainWindow.Register() || !mainWindow.Create(nCmdShow)) 
    {
        return 0;
    }
    return mainWindow.RunMessageLoop();
}