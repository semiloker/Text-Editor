#include "../include/top_bar.h"
#include <minwindef.h>
#include <windows.h>
#include <winuser.h>

TopBar::TopBar()
{
    file_manager = new FileManager();
}

void TopBar::CreateMenuBar(HWND hwnd)
{
    HMENU hMenu = CreateMenu();
    HMENU hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, MENU_FILE_LOAD, "Load");
    AppendMenu(hSubMenu, MF_STRING, MENU_FILE_SAVE, "Save");
    AppendMenu(hSubMenu, MF_SEPARATOR, NULL, "");
    AppendMenu(hSubMenu, MF_STRING, MENU_EXIT, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Menu");
    SetMenu(hwnd, hMenu);

    HMENU hGreekLetters = CreatePopupMenu();
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_ALPHA, "Alpha (α)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_BETA, "Beta (β)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_GAMMA, "Gamma (γ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_DELTA, "Delta (δ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_EPSILON, "Epsilon (ε)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_ZETA, "Zeta (ζ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_ETA, "Eta (η)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_THETA, "Theta (θ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_IOTA, "Iota (ι)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_KAPPA, "Kappa (κ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_LAMBDA, "Lambda (λ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_MU, "Mu (μ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_NU, "Nu (ν)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_XI, "Xi (ξ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_OMICRON, "Omicron (ο)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_PI, "Pi (π)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_RHO, "Rho (ρ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_SIGMA, "Sigma (σ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_TAU, "Tau (τ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_UPSILON, "Upsilon (υ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_PHI, "Phi (φ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_CHI, "Chi (χ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_PSI, "Psi (ψ)");
    AppendMenu(hGreekLetters, MF_STRING, MENU_INSERT_OMEGA, "Omega (ω)");
    
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hGreekLetters, "Greek Letters");

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

    case MENU_INSERT_ALPHA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"α");
        break;
    case MENU_INSERT_BETA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"β");
        break;
    case MENU_INSERT_GAMMA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"γ");
        break;
    case MENU_INSERT_DELTA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"δ");
        break;
    case MENU_INSERT_EPSILON:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"ε");
        break;
    case MENU_INSERT_ZETA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"ζ");
        break;
    case MENU_INSERT_ETA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"η");
        break;
    case MENU_INSERT_THETA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"θ");
        break;
    case MENU_INSERT_IOTA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"ι");
        break;
    case MENU_INSERT_KAPPA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"κ");
        break;
    case MENU_INSERT_LAMBDA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"λ");
        break;
    case MENU_INSERT_MU:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"μ");
        break;
    case MENU_INSERT_NU:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"ν");
        break;
    case MENU_INSERT_XI:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"ξ");
        break;
    case MENU_INSERT_OMICRON:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"ο");
        break;
    case MENU_INSERT_PI:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"π");
        break;
    case MENU_INSERT_RHO:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"ρ");
        break;
    case MENU_INSERT_SIGMA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"σ");
        break;
    case MENU_INSERT_TAU:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"τ");
        break;
    case MENU_INSERT_UPSILON:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"υ");
        break;
    case MENU_INSERT_PHI:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"φ");
        break;
    case MENU_INSERT_CHI:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"χ");
        break;
    case MENU_INSERT_PSI:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"ψ");
        break;
    case MENU_INSERT_OMEGA:
        SendMessageW(hEditText, EM_REPLACESEL, TRUE, (LPARAM)L"ω");
        break;
    }
}