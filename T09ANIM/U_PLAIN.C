/* FILE NAME: U_PLAIN.C
 * PROGRAMMER: AH5
 * DATE: 10.06.2017
 * PURPOSE: Units base functions.
 */

#include <stdio.h>
#include <math.h>
#include <time.h>

#include "units.h"

/* Animation unit representation type */
typedef struct tagUNIT_PLAIN
{
  AH5_UNIT_BASE_FIELDS;
  ah5PRIM Plain; /* Plain model */
} ah5UNIT_PLAIN;

/* Plain drawing unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_PLAIN *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitInit( ah5UNIT_PLAIN *Uni, ah5ANIM *Ani )
{
  AH5_RndPrimCreatePlane( &Uni->Plain, VecSet(-1500, 0, -1500), VecSet(3000, 0, 0), VecSet(0, 0, 3000), 500, 500);
} /* End of 'AH5_UnitInit' function */

/* Plain drawing unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_PLAIN *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitClose( ah5UNIT_PLAIN *Uni, ah5ANIM *Ani )
{
  AH5_RndPrimFree(&Uni->Plain);
} /* End of 'AH5_UnitClose' function */

/* Plain drawing unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_PLAIN *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitResponse( ah5UNIT_PLAIN *Uni, ah5ANIM *Ani )
{
} /* End of 'AH5_UnitResponse' function */

/* Plain drawing unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_PLAIN *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitRender( ah5UNIT_PLAIN *Uni, ah5ANIM *Ani )
{
  AH5_RndPrimDraw(&Uni->Plain, MatrMulMatr(UnitMatrix, MatrTranslate(VecSet(0, -10, 0))));
} /* End of 'AH5_UnitRender' function */

/* Plain drawing unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ah5UNIT *) pointer to created unit.
 */
ah5UNIT * AH5_UnitCreatePlain( VOID )
{
  ah5UNIT_PLAIN *Uni;

  /* Memory allocation */
  if ((Uni = (ah5UNIT_PLAIN *)AH5_AnimUnitCreate(sizeof(ah5UNIT_PLAIN))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AH5_UnitInit;
  Uni->Close = (VOID *)AH5_UnitClose;
  Uni->Response = (VOID *)AH5_UnitResponse;
  Uni->Render = (VOID *)AH5_UnitRender;
  return (ah5UNIT *)Uni;
} /* End of 'AH5_UnitCreatePlain' function */

/* END OF 'U_PLAIN.C' FILE */
