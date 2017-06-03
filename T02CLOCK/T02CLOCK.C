/* FILE NAME: T02CLOCK.C
 * PROGRAMMER: AH5
 * DATE: 02.06.2017
 * PURPOSE: clonck.
 */

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <windows.h>

#pragma warning(disable: 4244)

#define WND_CLASS_NAME "kazakhstan"

FLOAT pi = 3.1415926535F;
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
  HDC hDC;
  BITMAP bm;
  static HDC hMemDC, hMemDCLogo;
  static HBITMAP hBm, hBmXOR, hBmAND;
  static INT w, h, i;
  FLOAT sec, min, hou;
  PAINTSTRUCT ps;
  SYSTEMTIME st;
  POINT p[4];
  HFONT hFnt, hFntOld;

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDCLogo = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hBmAND = LoadImage(NULL, "1.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hBmXOR = LoadImage(NULL, "2.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    SetTimer(hWnd, 413, 10, NULL);
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
    SetDCBrushColor(hMemDC, RGB(220, 220, 220));

    /* Clear background */
    Rectangle(hMemDC, -1, -1, w + 1, h + 1);
    InvalidateRect(hWnd, NULL, FALSE);

    /* Draw clockface */
    GetObject(hBmXOR, sizeof(BITMAP), &bm);
    SetStretchBltMode(hMemDC, COLORONCOLOR);
    SelectObject(hMemDCLogo, hBmAND);
    BitBlt(hMemDC, (w - bm.bmWidth) / 2, (h - bm.bmHeight) / 2, bm.bmWidth, bm.bmHeight, hMemDCLogo, 0, 0, SRCAND);
    SelectObject(hMemDCLogo, hBmXOR);
    BitBlt(hMemDC, (w - bm.bmWidth) / 2, (h - bm.bmHeight) / 2, bm.bmWidth, bm.bmHeight, hMemDCLogo, 0, 0, SRCINVERT);

    /* Obtain current time */
    GetLocalTime(&st);
    sec = st.wSecond + st.wMilliseconds / 1000.0;
    min = st.wMinute + sec / 60.0;
    hou = st.wHour + min / 60.0;

    /* Output text */
    hFnt = CreateFont(120, 0, 500, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_ROMAN, "Bookman Old Style");
    hFntOld = SelectObject(hMemDC, hFnt);
    SetTextColor(hMemDC, RGB(5, 5, 5));
    SetBkMode(hMemDC, TRANSPARENT);                                               
    TextOut(hMemDC, 100, 300, "honk", 4);
    SelectObject(hMemDC, hFntOld);
    DeleteObject(hFnt);

    GetOpenFileName
    SetDCBrushColor(hMemDC, RGB(50, 50, 50));
    /* Draw second hand */
    p[0].x = w / 2;
    p[0].y = h / 2;
    p[1].x = w / 2 + 10 * cos((sec / 60.0) * pi * 2 - pi / 2 - 0.24);
    p[1].y = h / 2 + 10 * sin((sec / 60.0) * pi * 2 - pi / 2 - 0.24);
    p[2].x = w / 2 + 100 * cos((sec / 60.0) * pi * 2 - pi / 2);
    p[2].y = h / 2 + 100 * sin((sec / 60.0) * pi * 2 - pi / 2);
    p[3].x = w / 2 + 10 * cos((sec / 60.0) * pi * 2 - pi / 2 + 0.24);
    p[3].y = h / 2 + 10 * sin((sec / 60.0) * pi * 2 - pi / 2 + 0.24);
    Polygon(hMemDC, p, 4);

    /* Draw minute hand */
    p[0].x = w / 2;
    p[0].y = h / 2;
    p[1].x = w / 2 + 10 * cos((min / 60.0) * pi * 2 - pi / 2 - 0.5);
    p[1].y = h / 2 + 10 * sin((min / 60.0) * pi * 2 - pi / 2 - 0.5);
    p[2].x = w / 2 + 100 * cos((min / 60.0) * pi * 2 - pi / 2);
    p[2].y = h / 2 + 100 * sin((min / 60.0) * pi * 2 - pi / 2);
    p[3].x = w / 2 + 10 * cos((min / 60.0) * pi * 2 - pi / 2 + 0.5);
    p[3].y = h / 2 + 10 * sin((min / 60.0) * pi * 2 - pi / 2 + 0.5);
    Polygon(hMemDC, p, 4);

    /* Draw hour hand */
    p[0].x = w / 2;
    p[0].y = h / 2;
    p[1].x = w / 2 + 10 * cos((hou / 12.0) * pi * 2 - pi / 2 - 0.5);
    p[1].y = h / 2 + 10 * sin((hou / 12.0) * pi * 2 - pi / 2 - 0.5);
    p[2].x = w / 2 + 75 * cos((hou / 12.0) * pi * 2 - pi / 2);
    p[2].y = h / 2 + 75 * sin((hou / 12.0) * pi * 2 - pi / 2);
    p[3].x = w / 2 + 10 * cos((hou / 12.0) * pi * 2 - pi / 2 + 0.5);
    p[3].y = h / 2 + 10 * sin((hou / 12.0) * pi * 2 - pi / 2 + 0.5);
    Polygon(hMemDC, p, 4);
    return 0;
  case WM_ERASEBKGND:
    return 1;
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
    KillTimer(hWnd, 413);
    PostQuitMessage(413612);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
