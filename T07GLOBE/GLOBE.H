/* FILE NAME: GLOBE.H
 * PROGRAMMER: AH5
 * DATE: 07.06.2017
 * PURPOSE: ooooooooooooooooooooooooo
 */

#include <windows.h>

#define GRID_W 60
#define GRID_H 30
#define pi 3.14159265358979323846

typedef double DBL;
typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;
typedef struct tagMATR
{
  DBL A[3][3];
} MATR;

static VEC G[GRID_H][GRID_W];
static POINT Pts[GRID_H][GRID_W];

VOID DrawSphere( HDC hMemDC, INT w, INT h );
VOID BuildSphere( DBL R );
MATR MatrRotate( DBL AngleInDegree, VEC R );
VEC VecTransform( VEC V, MATR M );