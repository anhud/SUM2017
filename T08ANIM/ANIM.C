/* FILE NAME: ANIM.C
 * PROGRAMMER: AH5
 * DATE: 09.06.2017
 * PURPOSE: no 
 */

#include "anim.h"

#include <mmsystem.h>

#pragma comment(lib, "winmm")

/* Joystic axis value determination */
#define AH5_GET_JOYSTICK_AXIS(A) \
  (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min - 1) - 1)

ah5ANIM AH5_Anim;
INT AH5_MouseWheel;

static UINT64
  AH5_StartTime,  /* Start program time */
  AH5_OldTime,    /* Time from program start to previous frame */
  AH5_OldTimeFPS, /* Old time FPS measurement */
  AH5_PauseTime,  /* Time during pause period */
  AH5_TimePerSec, /* Timer resolution */
  AH5_FrameCounter; /* Frames counter */

LARGE_INTEGER t;

VOID AH5_AnimInit( HWND hWnd )
{
  HDC hDC;

  memset(&AH5_Anim, 0, sizeof(ah5ANIM));

  AH5_Anim.hWnd = hWnd;
  hDC = GetDC(AH5_Anim.hWnd);
  AH5_Anim.hDC = CreateCompatibleDC(hDC);
  ReleaseDC(AH5_Anim.hWnd, hDC);

  AH5_RndInit();

  QueryPerformanceFrequency(&t);
  AH5_TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  AH5_StartTime = AH5_OldTime = AH5_OldTimeFPS = t.QuadPart;
  AH5_PauseTime = 0;

  AH5_FrameCounter = 0;
  AH5_Anim.IsPause = FALSE;
  AH5_Anim.FPS = 50;
}

VOID AH5_AnimClose( VOID )
{
  INT i;

  for(i = 0; i < AH5_Anim.NumOfUnits; i++)
  {
    AH5_Anim.Units[i]->Close(AH5_Anim.Units[i], &AH5_Anim);
    free(AH5_Anim.Units[i]);
  }

  DeleteObject(AH5_Anim.hBm);
  DeleteDC(AH5_Anim.hDC);
  memset(&AH5_Anim, 0, sizeof(ah5ANIM));
}

VOID AH5_AnimResize( INT W, INT H )
{
  HDC hDC;

  /* Store new size */
  AH5_Anim.W = W;
  AH5_Anim.H = H;

  /* Resize frame image */
  if (AH5_Anim.hBm != NULL)
    DeleteObject(AH5_Anim.hBm);
  hDC = GetDC(AH5_Anim.hWnd);
  AH5_Anim.hBm = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(AH5_Anim.hWnd, hDC);

  SelectObject(AH5_Anim.hDC, AH5_Anim.hBm);
  AH5_RndSetProj();
}

VOID AH5_AnimCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, AH5_Anim.W, AH5_Anim.H, AH5_Anim.hDC, 0, 0, SRCCOPY);
}

VOID AH5_AnimRender( VOID )                                                     
{
  INT i;
  LARGE_INTEGER t;
  POINT pt;

  for (i = 0; i < AH5_Anim.NumOfUnits; i++)
    AH5_Anim.Units[i]->Response(AH5_Anim.Units[i], &AH5_Anim);
  
  SelectObject(AH5_Anim.hDC, GetStockObject(DC_PEN));
  SelectObject(AH5_Anim.hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(AH5_Anim.hDC, RGB(120, 120, 122));
  Rectangle(AH5_Anim.hDC, -1, -1, AH5_Anim.W + 1, AH5_Anim.H + 1);

  for (i = 0; i < AH5_Anim.NumOfUnits; i++)
  {
    SetDCPenColor(AH5_Anim.hDC, RGB(0, 220, 0));
    AH5_Anim.Units[i]->Render(AH5_Anim.Units[i], &AH5_Anim);
  }

  /*** Handle timer ***/
  AH5_FrameCounter++;                   
  QueryPerformanceCounter(&t);          
  /* Global time */
  AH5_Anim.GlobalTime = (DBL)(t.QuadPart - AH5_StartTime) / AH5_TimePerSec;
  AH5_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - AH5_OldTime) / AH5_TimePerSec;
  /* Time with pause */
  if (AH5_Anim.IsPause)
  {
    AH5_PauseTime += t.QuadPart - AH5_OldTime;
    AH5_Anim.DeltaTime = 0;
  }
  else
  {
    AH5_Anim.Time = (DBL)(t.QuadPart - AH5_PauseTime - AH5_StartTime) / AH5_TimePerSec;
    AH5_Anim.DeltaTime = AH5_Anim.GlobalDeltaTime;
  }
  /* FPS */
  if (t.QuadPart - AH5_OldTimeFPS > AH5_TimePerSec)
  {
    AH5_Anim.FPS = (DBL)AH5_FrameCounter * AH5_TimePerSec / (t.QuadPart - AH5_OldTimeFPS);
    AH5_OldTimeFPS = t.QuadPart;
    AH5_FrameCounter = 0;
  }
  AH5_OldTime = t.QuadPart;

  GetKeyboardState(AH5_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    AH5_Anim.Keys[i] >>= 7;
    AH5_Anim.KeysClick[i] = AH5_Anim.Keys[i] && !AH5_Anim.KeysOld[i];
  }
  memcpy(AH5_Anim.KeysOld, AH5_Anim.Keys, 256);

  GetCursorPos(&pt);
  ScreenToClient(AH5_Anim.hWnd, &pt);
  AH5_Anim.Mdx = pt.x - AH5_Anim.Mx;
  AH5_Anim.Mdy = pt.y - AH5_Anim.My;
  AH5_Anim.Mx = pt.x;
  AH5_Anim.My = pt.y;

  AH5_Anim.Mdz = AH5_MouseWheel;
  AH5_Anim.Mz += AH5_MouseWheel;
  AH5_MouseWheel = 0;

  /*** Joystick handle ***/
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(JOYCAPS)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Axes */
        AH5_Anim.Jx = AH5_GET_JOYSTICK_AXIS(X);
        AH5_Anim.Jy = AH5_GET_JOYSTICK_AXIS(Y);
        AH5_Anim.Jz = AH5_GET_JOYSTICK_AXIS(Z);
        AH5_Anim.Jr = AH5_GET_JOYSTICK_AXIS(R);

        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          AH5_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          AH5_Anim.JButClick[i] = AH5_Anim.JBut[i] && !AH5_Anim.JButOld[i];
          memcpy(AH5_Anim.JButOld, AH5_Anim.JBut, 32);
        }

        /* Point of view */
        AH5_Anim.JPov = ji.dwPOV == 0xFFFF ? 0 : ji.dwPOV / 4500 + 1;
      }
    }
  }
}

VOID AH5_AnimAddUnit( ah5UNIT *Uni )
{
  if (AH5_Anim.NumOfUnits < AH5_MAX_UNITS)
  {
    AH5_Anim.Units[AH5_Anim.NumOfUnits++] = Uni;
    Uni->Init(Uni, &AH5_Anim);
  }
}

VOID AH5_AnimFlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  if (IsFullScreen)
  {
    /* restore window size */
    SetWindowPos(AH5_Anim.hWnd, HWND_TOP,
      SaveRect.left, SaveRect.top,         rt
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
    GetWindowRect(AH5_Anim.hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(AH5_Anim.hWnd, MONITOR_DEFAULTTONEAREST);

    /* Obtain monitor info */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    /* Set window new size */
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(AH5_Anim.hWnd, GWL_STYLE), FALSE);

    SetWindowPos(AH5_Anim.hWnd, HWND_TOPMOST,
      rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  IsFullScreen = !IsFullScreen;
}