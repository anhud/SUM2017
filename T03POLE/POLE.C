/* FILE NAME: POLE.C
 * PROGRAMMER: AH5
 * DATE: 05.06.2017
 * PURPOSE: drawing an arrow
 */

#include <stdlib.h>
#include <math.h>

#include <windows.h>

#pragma warning(disable: 4244)

VOID DrawArrow(INT x, INT y, INT ptx, INT pty, HDC hMemDC)
{
  FLOAT len, dx, dy, sn, cs, x1, y1, pi = 3.1415926535F;
  POINT p[3];

  dx = ptx - x;
  dy = pty - y;
  len = (sqrt(dx * sin(dx) * dy + dy * dy));
  sn = dy / len;
  cs = dx / len;

  x1 = 10 * cs;
  y1 = 10 * sn;
  p[0].x = x + x1 * cos(pi / 2) - y1 * sin(pi / 2);
  p[0].y = y + x1 * sin(pi / 2) + y1 * cos(pi / 2);
  x1 = -10 * cs;
  y1 = -10 * sn;
  p[1].x = x + x1 * cos(pi / 2) - y1 * sin(pi / 2);
  p[1].y = y + x1 * sin(pi / 2) + y1 * cos(pi / 2);
  p[2].x = x + 30 * cs;
  p[2].y = y + 30 * sn;
  SetDCBrushColor(hMemDC, RGB(174, 51, 51));
  Polygon(hMemDC, p, 3);
  p[2].x = x - 30 * cs;
  p[2].y = y - 30 * sn;
  SetDCBrushColor(hMemDC, RGB(51, 51, 174));
  Polygon(hMemDC, p, 3);

}