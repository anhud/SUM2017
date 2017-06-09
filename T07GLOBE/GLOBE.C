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
  DBL size = 1, wp = size, hp = size, xp, yp, t = clock() * 50 / (DBL)CLOCKS_PER_SEC;
  INT i, j, i1, j1;
  VEC RT = {2, -3, 0.5};

  if (w < h)
    hp *= (DBL)h / w;
  else
    wp *= (DBL)w / h;

  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      G[i][j] = VecTransform(G[i][j], (MatrRotate(t, RT)));
      xp = G[i][j].X;
      yp = G[i][j].Y;

      Pts[i][j].x = xp * w / wp + w / 2;
      Pts[i][j].y = h / 2 - yp * h / hp;
    }

 for(i = 0; i < GRID_H; i++)
   for(j = 0; j < GRID_W; j++)
   {
     i1 = i + 1;
     if ((GRID_W - j) != 1)
       j1 = j + 1;
     else
       j1 = 0;
     if(((Pts[i][j].x - Pts[i][j1].x) * (Pts[i][j].y + Pts[i][j1].y) + (Pts[i][j1].x - Pts[i1][j1].x) * (Pts[i][j1].y + Pts[i1][j1].y) + (Pts[i1][j1].x - Pts[i1][j].x) * (Pts[i1][j1].y + Pts[i1][j].y) + (Pts[i1][j].x - Pts[i][j].x) * (Pts[i1][j].y + Pts[i][j].y)) >= 0)
     {  
       MoveToEx(hMemDC, Pts[i][j].x, Pts[i][j].y, NULL);
       LineTo(hMemDC, Pts[i][j1].x, Pts[i][j1].y);
       MoveToEx(hMemDC, Pts[i][j].x, Pts[i][j].y, NULL);
       LineTo(hMemDC, Pts[i1][j].x, Pts[i1][j].y);
     }
   }
}

VOID BuildSphere( DBL R )
{
  DBL theta, phi, x, y, z;
  INT i, j;

  for(theta = 0, i = 0; i < GRID_H; i++ , theta += pi / (GRID_H - 1))
    for(phi = 0, j = 0; j < GRID_W; j++, phi += 2 * pi / GRID_W)
    {
      x = (R * sin(theta) * sin(phi));
      y = (R * cos(theta));
      z = (R * sin(theta) * cos(phi));

      G[i][j].X = x ;
      G[i][j].Y = y ;
      G[i][j].Z = z ;
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