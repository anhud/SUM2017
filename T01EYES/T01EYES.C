/* FILE NAME: T01EYES.C
 * PROGRAMMER: AH5
 * DATE: 01.06.2017
 * PURPOSE: WinAPI windowed application sample.
 */

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <windows.h>

#define WND_CLASS_NAME "kazakhstan"

/* Forward references */
INT CALLBACK MyWindowFunc( HWND hWnd, unsigned Message,
                           WPARAM wParam, LPARAM lParam );

/* Main program function */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_WAIT);
  wc.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "error register window class", "ERROR", MB_OK);
    return 0;
  }

  hWnd =
    CreateWindow(WND_CLASS_NAME,
    "BOJANGLES",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL);
  
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

VOID DrawEye (HDC hDC, INT Xc, INT Yc, INT X, INT Y, INT R, FLOAT j) 
{
  INT dx = X - Xc, dy = Y - Yc;
  FLOAT len = sqrt(dx * dx + dy * dy), si = dy / len, co = dx / len, q;
  SelectObject(hDC, GetStockObject(DC_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  q = ((rand() % 8) / 2 + 1) * cos(cos(j));
  SetDCPenColor(hDC, RGB(20, 20, 20));
  SetDCBrushColor(hDC, RGB(255 * sqrt(log(tanh(j))), 255 * sin(j), 255 * cos(j)));
  Ellipse(hDC, Xc - 20 * q, Yc - 20 * q, Xc + 20 * q, Yc + 20 * q);
  SetDCBrushColor(hDC, RGB(128 * sin(j), 128 * cos(j), 128 * tanh(j)));
  Ellipse(hDC, Xc + (12 * co - 8) * q, Yc + (12 * si - 8) * q, Xc + (12 * co + 8) * q, Yc + (12 * si + 8) * q);
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  INT i, x, y;
  static HDC hMemDC;
  static HBITMAP hBm;
  static INT w, h;
  FLOAT j;
  PAINTSTRUCT ps;
  POINT pt;

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 47, 10, NULL);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_TIMER:
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);                

    j = clock();
    srand(413);
    hDC = GetDC(hWnd);
    for(i = 0; i < 150; i++)
    {
      x = rand() % (w + 1) * cos(sin(j / 2));
      y = rand() % (h + 1) * cos(j);
      DrawEye(hMemDC, x, y, pt.x, pt.y, 30, j);
    }
    InvalidateRect(hWnd, NULL, FALSE);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
    {
      DestroyWindow(hWnd);
      InvalidateRect(hWnd, NULL, FALSE);
    }
    return 0;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 47);
    PostQuitMessage(413612);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
