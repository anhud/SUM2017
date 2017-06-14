/* FILE NAME: OBJ3D.C
 * PROGRAMMER: AH5
 * DATE: 10.06.2017
 * PURPOSE: Object handle module.
 */

#include <stdio.h>

#include "anim.h"

/* Object free memory function.
 * ARGUMENTS:
 *   - object pointer:
 *       ah5OBJ3D *Obj;
 *   - model *.OBJ file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL AH5_RndObjLoad( ah5OBJ3D *Obj, CHAR *FileName )
{
  INT vn = 0, fn = 0, size;
  FILE *F;
  static CHAR Buf[1000];

  memset(Obj, 0, sizeof(ah5OBJ3D));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count quantities */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      vn++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      fn++;
  }

  /* Memory allocation */
  size = sizeof(VEC) * vn + sizeof(INT [3]) * fn;
  if ((Obj->V = malloc(size)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  Obj->F = (INT (*)[3])(Obj->V + vn);
  Obj->NumOfV = vn;
  Obj->NumOfF = fn;

  /* Read model data */
  rewind(F);
  vn = 0;
  fn = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Obj->V[vn++] = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n0, n1, n2;

      if (sscanf(Buf + 2, "%i/%*i/%*i %i/%*i/%*i %i/%*i/%*i", &n0, &n1, &n2) == 3 ||
          sscanf(Buf + 2, "%i//%*i %i//%*i %i//%*i", &n0, &n1, &n2) == 3 ||
          sscanf(Buf + 2, "%i/%*i %i/%*i %i/%*i", &n0, &n1, &n2) == 3 ||
          sscanf(Buf + 2, "%i %i %i", &n0, &n1, &n2) == 3)
      {
        Obj->F[fn][0] = n0 - 1;
        Obj->F[fn][1] = n1 - 1;
        Obj->F[fn][2] = n2 - 1;
        fn++;
      }
    }
  }

  fclose(F);
  return TRUE;
} /* End of 'AH5_RndObjLoad' function */

/* Object free memory function.
 * ARGUMENTS:
 *   - object pointer:
 *       ah5OBJ3D *Obj;
 * RETURNS: None.
 */
VOID AH5_RndObjFree( ah5OBJ3D *Obj )
{
  if (Obj->V != NULL)
    free(Obj->V);
  memset(Obj, 0, sizeof(ah5OBJ3D));
} /* End of 'AH5_RndObjFree function */

/* Object drawing function.
 * ARGUMENTS:
 *   - object pointer:
 *       ah5OBJ3D *Obj;
 *   - world coordinate system transform matrix:
 *       MATR M;
 * RETURNS: None.
 */
VOID AH5_RndObjDraw( ah5OBJ3D *Obj, MATR M )
{
  INT i;
  POINT *pts;
  MATR WVP;

  if ((pts = malloc(sizeof(POINT) * Obj->NumOfV)) == NULL)
    return;

  WVP = MatrMulMatr(M, MatrMulMatr(AH5_RndMatrView, AH5_RndMatrProj));
  SetDCBrushColor(AH5_Anim.hDC, RGB(120, 120, 122));
  /* Project all points */
  for (i = 0; i < Obj->NumOfV; i++)
  {
    VEC p = VecMulMatr43(Obj->V[i], WVP);

    pts[i].x = (p.X + 1) * AH5_Anim.W / 2;
    pts[i].y = (-p.Y + 1) * AH5_Anim.H / 2;
  }
  for(i = 0; i < Obj->NumOfF; i++)
  {
    POINT px[3];

    px[0] = pts[Obj->F[i][0]];
    px[1] = pts[Obj->F[i][1]];
    px[2] = pts[Obj->F[i][2]];
    Polygon(AH5_Anim.hDC, px, 3);
  }
  free(pts); 
} /* End of 'AH5_RndObjDraw' function */

/* END OF 'OBJ3D.C' FILE */
