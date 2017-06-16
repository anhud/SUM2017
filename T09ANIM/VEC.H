/* FILE NAME: VEC.H
 * PROGRAMMER: AH5
 * DATE: 07.06.2017
 * PURPOSE: blblblblblblblblbl
 */

#ifndef __VEC_H
#define __VEC_H

#include <math.h>

#include <windows.h>

#define PI 3.141592653589793238462643383
#define D2R(A) ((A) * PI / 180.0)
#define DegreeToRadian(a) D2R(a)

typedef double DBL;
typedef float FLT;
typedef struct tagVEC
{
  FLT X, Y, Z;
} VEC;
typedef struct tagVEC2
{
  FLT X, Y;
} VEC2;
typedef struct tagVEC4
{
  FLT X, Y, Z, W;
} VEC4;
typedef struct tagMATR
{
  FLT M[4][4];
} MATR;

static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  return v;
}

__inline VEC VecSet1( DBL X )
{
  VEC v;

  v.X = X;
  v.Y = X;
  v.Z = X;
  return v;
}

__inline VEC4 Vec4Set( DBL X, DBL Y, DBL Z, DBL W )
{
  VEC4 v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  v.W = W;
  return v;
}

__inline VEC2 Vec2Set( DBL X, DBL Y )
{
  VEC2 v;

  v.X = X;
  v.Y = Y;
  return v;
}

__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}
__inline VEC VecMulNum( VEC V, DBL N )
{
  return VecSet(V.X * N, V.Y * N, V.Z * N);
}
__inline VEC VecDivNum( VEC V, DBL N )
{
  return VecSet(V.X / N, V.Y / N, V.Z / N);
}
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return (V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z);
}
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}
__inline DBL VecLen2( VEC V )
{
  return (V.X * V.X + V.Y * V.Y + V.Z * V.Z);
}
__inline DBL VecLen( VEC V )
{
  return sqrt(VecLen2(V));
}
__inline VEC VecNormalize( VEC V )
{
  return VecSet(V.X / VecLen(V), V.Y / VecLen(V), V.Z / VecLen(V));
}

__inline VEC VecAddVecEq( VEC *VRes, VEC V2 )
{
  VRes->X += V2.X;
  VRes->Y += V2.Y;
  VRes->Z += V2.Z;
  return *VRes;
}

__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}
__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.M[3][0] = T.X;
  m.M[3][1] = T.Y;
  m.M[3][2] = T.Z;
  return m;
}
__inline MATR MatrScale( VEC S )
{
  MATR r = UnitMatrix;

  r.M[0][0] = S.X;
  r.M[1][1] = S.Y;
  r.M[2][2] = S.Z;

  return r;
}

__inline MATR MatrRotateX( DBL AngleInDegree )
{
  MATR r = UnitMatrix;

  r.M[1][1] = cos(AngleInDegree);
  r.M[1][2] = sin(AngleInDegree);
  r.M[2][1] = -r.M[1][2];
  r.M[2][2] = r.M[1][1];

  return r;
}
__inline MATR MatrRotateY( DBL AngleInDegree )
{
  MATR r = UnitMatrix;

  r.M[0][0] = cos(AngleInDegree);
  r.M[2][0] = sin(AngleInDegree);
  r.M[0][2] = -r.M[2][0];
  r.M[2][2] = r.M[0][0];

  return r;
}
__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  MATR r = UnitMatrix;

  r.M[0][0] = cos(AngleInDegree);
  r.M[0][1] = sin(AngleInDegree);
  r.M[1][0] = -r.M[0][1];
  r.M[1][1] = r.M[0][0];

  return r;
}
__inline MATR MatrMulMatr3( MATR M1, MATR M2, MATR M3 )
{
  MATR r, r1;
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.M[i][j] = 0, k = 0; k < 4; k++)
        r.M[i][j] += M1.M[i][k] * M2.M[k][j];
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
       for (r1.M[i][j] = 0, k = 0; k < 4; k++)
       r1.M[i][j] += r.M[i][k] * M3.M[k][j];
  return r1;
}
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r;
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.M[i][j] = 0, k = 0; k < 4; k++)
        r.M[i][j] += M1.M[i][k] * M2.M[k][j];
  return r;
}
__inline MATR MatrTranspose( MATR M )
{
  MATR r;
  INT i, j;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      r.M[i][j] = M.M[j][i];
  return r;
}

__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33  )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
}
__inline DBL MatrDeterm( MATR M )
{
  return
    M.M[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                              M.M[2][1], M.M[2][2], M.M[2][3],
                              M.M[3][1], M.M[3][2], M.M[3][3]) -
    M.M[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                              M.M[2][0], M.M[2][2], M.M[2][3],
                              M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.M[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                              M.M[2][0], M.M[2][1], M.M[2][3],
                              M.M[3][0], M.M[3][1], M.M[3][3]) -
    M.M[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                              M.M[2][0], M.M[2][1], M.M[2][2],
                              M.M[3][0], M.M[3][1], M.M[3][2]);
}
__inline MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);
  INT p[4][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}}, i, j;

  if (det == 0)
    return UnitMatrix;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      r.M[j][i] =
        MatrDeterm3x3(
          M.M[p[i][0]][p[j][0]], M.M[p[i][0]][p[j][1]], M.M[p[i][0]][p[j][2]],
          M.M[p[i][1]][p[j][0]], M.M[p[i][1]][p[j][1]], M.M[p[i][1]][p[j][2]],
          M.M[p[i][2]][p[j][0]], M.M[p[i][2]][p[j][1]], M.M[p[i][2]][p[j][2]]) / det;
  return r;
}
__inline MATR MatrRotate( DBL AngleInDegrees, VEC R )
{
  DBL A = D2R(AngleInDegrees), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);
  MATR M =
  {
    {
      {co + V.X * V.X * (1 - co),
         V.X * V.Y * (1 - co) - V.Z * si,
           V.X * V.Z * (1 - co) + V.Y * si, 0},
      {V.Y * V.X * (1 - co) + V.Z * si,
         co + V.Y * V.Y * (1 - co),
           V.Y * V.Z * (1 - co) - V.X * si, 0},
      {V.Z * V.X * (1 - co) - V.Y * si,
         V.Z * V.Y * (1 - co) + V.X * si,
           co + V.Z * V.Z * (1 - co),       0},
      {0, 0, 0, 1}
    }
  };
  return M;
}      
__inline VEC VecMulMatr43( VEC V, MATR M )
{
  return VecSet(V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0],
                V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1],
                V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]);
}
__inline VEC VecMulMatr3( VEC V, MATR M )
{
  return VecSet(V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0],
                V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1],
                V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2]);
}
__inline VEC PointTransform( VEC V, MATR M )
{
  FLT w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];

  return VecSet((V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0]) / w,
                (V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1]) / w,
                (V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]) / w);
}

__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m =
  {
    {
      {               Right.X,                Up.X,              -Dir.X, 0},
      {               Right.Y,                Up.Y,              -Dir.Y, 0},
      {               Right.Z,                Up.Z,              -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
}

__inline MATR MatrFrustum( DBL l, DBL r, DBL b, DBL t, DBL n, DBL f )
{
  MATR m;

  m.M[0][0] = (2 * n) / (r - l);
  m.M[0][1] = 0;
  m.M[0][2] = 0;
  m.M[0][3] = 0;

  m.M[1][0] = 0;
  m.M[1][1] = (2 * n) / (t - b);
  m.M[1][2] = 0;
  m.M[1][3] = 0;

  m.M[2][0] = (r + l) / (r - l);
  m.M[2][1] = (t + b) / (t - b);
  m.M[2][2] = -(f + n) / (f - n);
  m.M[2][3] = -1;

  m.M[3][0] = 0;
  m.M[3][1] = 0;
  m.M[3][2] = -(2 * n * f) / (f - n);
  m.M[3][3] = 0;

  return m;
}
#endif