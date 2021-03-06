/* FILE NAME: T07GLOBE.C
 * PROGRAMMER: AH5
 * DATE: 07.06.2017
 * PURPOSE: glob
 */

#include <stdlib.h>
#include "globe.h"

#include <windows.h>

#pragma warning(disable: 4244)

#define WND_CLASS_NAME "kazakhstan"

/* Forward references */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
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
    "shame",
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

VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  if (IsFullScreen)
  {
    /* restore window size */
    SetWindowPos(hWnd, HWND_TOP,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    /* Set full screen size to window */
    HMONITOR hmon;
    MONITORINFOEX moninfo;
    RECT rc;

    /* Store window old size */
    GetWindowRect(hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    /* Obtain monitor info */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    /* Set window new size */
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOPMOST,
      rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  IsFullScreen = !IsFullScreen;
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static HDC hMemDC;
  static INT w, h, mode;
  static HBITMAP hBm;
  DBL R = 0.4;
  MINMAXINFO *MinMax;
//  INT x, y;
//  POINT pt; 

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 413, 10, NULL);
    return 0;
  case WM_GETMINMAXINFO:
    MinMax = (MINMAXINFO *)lParam;
    MinMax->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
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
    SendMessage(hWnd, WM_TIMER, 413, 0);                              
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_TIMER:             
    SelectObject(hMemDC, GetStockObject(DC_PEN));
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCPenColor(hMemDC, RGB(0, 0, 0));
    SetDCBrushColor(hMemDC, RGB(200, 200, 200));

    /* Clear background */
    Rectangle(hMemDC, -1, -1, w + 1, h + 1);
    InvalidateRect(hWnd, NULL, FALSE);

    DrawSphere(hMemDC, w, h);
    BuildSphere(R);

    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
    {                                                                                                      
      DestroyWindow(hWnd);
      InvalidateRect(hWnd, NULL, FALSE);
    }
    if (wParam == '1')
      mode = 1;
    if (wParam == '2')
      mode = 2;
    if (wParam == '3')
      mode = 3;
    if (wParam == 'F')
      FlipFullScreen(hWnd);
    return 0;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 413);
    PostQuitMessage(413612);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}

