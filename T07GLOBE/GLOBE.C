/* FILE NAME: GLOBE.C
 * PROGRAMMER: AH5
 * DATE: 07.06.2017
 * PURPOSE: drawing something
 */

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "globe.h"

#include <windows.h>

#pragma warning(disable: 4244)

VOID DrawSphere( HDC hMemDC, INT w, INT h )
{
  DBL size = 1, wp = size, hp = size, xp, yp, t = clock() / (DBL)CLOCKS_PER_SEC;
  INT i, j;

  if (w < h)
    hp *= (DBL)h / w;
  else
    wp *= (DBL)w / h;

  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      xp = G[i][j].X * sin(t) - G[i][j].Y * cos(t);
      yp = G[i][j].X * cos(t) + G[i][j].Y * sin(t);

      Pts[i][j].x = xp * w / wp + w / 2;
      Pts[i][j].y = h / 2 - yp * h / hp;
    }

  /*points*/
  for(i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      Ellipse(hMemDC, Pts[i][j].x - 2, Pts[i][j].y - 2, Pts[i][j].x + 2, Pts[i][j].y + 2);
    }

 for(i = 0; i < GRID_H; i++)
  {
    MoveToEx(hMemDC, Pts[i][0].x, Pts[i][0].y, NULL);
    LineTo(hMemDC, Pts[i][1].x, Pts[i][1].y);
  }
}

VOID BuildSphere( DBL R )
{
  DBL theta, phi, x, y, z;
  INT i, j;

  for(theta = 0, i = 0; i < GRID_H; i++ , theta += pi / (GRID_H - 1))
    for(phi = 0, j = 0; j < GRID_W; j++, phi += 2 * pi / GRID_W)
    {
      x = R * sin(theta) * sin(phi);
      y = R * cos(theta);
      z = R * sin(theta) * cos(phi);

      G[i][j].X = x;
      G[i][j].Y = y;
      G[i][j].Z = z;
    }
}

MATR MatrRotate( DBL AngleInDegree, VEC R )
{
  DBL a = AngleInDegree * pi / 180, sine = sin(a), cosine = cos(a);
  MATR m;

  a = sqrt(R.X * R.X + R.Y * R.Y + R.Z * R.Z);
  R.X /= a;
  R.Y /= a;
  R.Z /= a;

  m.A[0][0] = cosine + R.X * R.X * (1 - cosine);
  m.A[0][1] = R.X * R.Y * (1 - cosine) - R.Z * sine;
  m.A[0][2] = R.X * R.Z * (1 - cosine) + R.Y * sine;

  m.A[1][0] = R.Y * R.X * (1 - cosine) + R.Z * sine;
  m.A[1][1] = cosine + R.Y * R.Y * (1 - cosine);
  m.A[1][2] = R.Y * R.Z * (1 - cosine) - R.X * sine;

  m.A[2][0] = R.Z * R.X * (1 - cosine) - R.Y * sine;
  m.A[2][1] = R.Z * R.Y * (1 - cosine) + R.X * sine;
  m.A[2][2] = cosine + R.Z * R.Z * (1 - cosine);
  return m;
}

VEC VecTransform( VEC V, MATR M )
{
  VEC P =
  {
    V.X * M.A[0][0] + V.Y * M.A[0][1] + V.Z * M.A[0][2],
    V.X * M.A[1][0] + V.Y * M.A[1][1] + V.Z * M.A[1][2],
    V.X * M.A[2][0] + V.Y * M.A[2][1] + V.Z * M.A[2][2]
  };

  return P;
}