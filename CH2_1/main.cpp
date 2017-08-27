#include <Windows.h>
#include <windowsx.h> 

#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#define WIN32_LEAN_AND_MEAN

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    //std::cout << "msg : " << msg << std::endl;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (msg)
    {
    case WM_CREATE:
    {
        return 0;
        break;
    }
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        EndPaint(hwnd, &ps);
        return 0;
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
        break;
    }
    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

void GameMain()
{

}

int WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    if (AllocConsole())
    {
        freopen("CONOUT$", "w", stdout);
        printf("hello, world!");
    }

    WNDCLASSEX wndClass;
    wndClass.cbSize = sizeof(wndClass);
    wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;
    wndClass.lpfnWndProc = WinProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = "WINCLASSCH2_1";
    wndClass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);


    if (!RegisterClassEx(&wndClass))
    {
        return 0;
    }

    HWND hwnd = CreateWindowEx(NULL,
        "WINCLASSCH2_1",
        "My First Window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        400,
        400,
        NULL,
        NULL,
        hInstance,
        NULL);
    if (hwnd == NULL)
    {
        //TODO ERROR
        return 0;
    }

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        GameMain(); 
    }

    FreeConsole();
    return msg.wParam;
}