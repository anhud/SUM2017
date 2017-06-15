/* FILE NAME: OBJ.C
 * PROGRAMMER: AH5
 * DATE: 14.06.2017
 * PURPOSE: Object handle module.
 */

#include <stdio.h>

#include "anim.h"

/* Create object function.
 * ARGUMENTS:
 *   - created object:
 *       ah5OBJ *Obj;
 *   - number of primitives:
 *       INT NumOfP;
* RETURNS: None.
 */
VOID AH5_RndObjCreate( ah5OBJ *Obj, INT NumOfP )
{
  memset(Obj, 0, sizeof(ah5PRIM));
  if ((Obj->P = malloc(sizeof(ah5PRIM) * NumOfP)) == NULL)
    return;
  memset(Obj->P, 0, sizeof(ah5PRIM) * NumOfP);
  Obj->NumOfP = NumOfP;
} /* Ens of 'AH5_RndObjCreate' function */

/* Free object function.
 * ARGUMENTS:
 *   - deleted object:
 *       ah5OBJ *Obj;
 * RETURNS: None.
 */
VOID AH5_RndObjFree( ah5OBJ *Obj )
{
  INT i;

  for (i = 0; i < Obj->NumOfP; i++)
    AH5_RndPrimFree(&Obj->P[i]);
  free(Obj->P);
  memset(Obj, 0, sizeof(ah5PRIM));
} /* Ens of 'AH5_RndObjFree' function */

/* Draw primitive function.
 * ARGUMENTS:
 *   - drawing object:
 *       ah5OBJ *Obj;
 *   - transformation matrix:
 *       MATR M;
 * RETURNS: None.
 */
VOID AH5_RndObjDraw( ah5OBJ *Obj, MATR M )
{
  INT i;

  for (i = 0; i < Obj->NumOfP; i++)
    AH5_RndPrimDraw(&Obj->P[i], M);
} /* Ens of 'AH5_RndObjDraw' function */

/* END OF 'OBJ.C' FILE */
