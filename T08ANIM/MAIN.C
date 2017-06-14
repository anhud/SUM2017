/* FILE NAME: TEST.C
 * PROGRAMMER: AH5
 * DATE: 10.06.2017
 * PURPOSE: clofgdgfdnck.
 */

#include <stdlib.h>
#include <math.h>
#include "anim.h"
#include "units.h"

#include <windows.h>

#pragma warning(disable: 4244)

#define WND_CLASS_NAME "kazakhstan"

INT AH5_MouseWheel;

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
    "smh",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL);
  
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  /* AH5_AnimAddUnit(AH5_UnitCreateBall());   */
  AH5_AnimAddUnit(AH5_UnitCreateControl());
  AH5_AnimAddUnit(AH5_UnitCreateCow());
  
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  INT w, h;
  HDC hDC;
  PAINTSTRUCT ps;
  MINMAXINFO *MinMax;

  switch (Msg)
  {
  case WM_CREATE:
    AH5_AnimInit(hWnd);
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
    AH5_AnimResize(w, h);
    AH5_AnimRender();
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    AH5_AnimCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_TIMER:
    AH5_AnimRender();
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      DestroyWindow(hWnd);
    else if (wParam == 'F')
      AH5_AnimFlipFullScreen();
    return 0;
  case WM_MOUSEWHEEL:
    AH5_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 413);
    PostQuitMessage(413612);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
