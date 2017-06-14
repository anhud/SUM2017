/* FILE NAME: U_COW.C
 * PROGRAMMER: AH5
 * DATE: 10.06.2017
 * PURPOSE: Units base functions.
 */

#include <stdio.h>
#include <math.h>
#include <time.h>

#include "units.h"

/* Animation unit representation type */
typedef struct tagUNIT_COW
{
  AH5_UNIT_BASE_FIELDS;
  ah5OBJ3D Cow; /* Cow model */
} ah5UNIT_COW;

/* Cow drawing unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_COW *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitInit( ah5UNIT_COW *Uni, ah5ANIM *Ani )
{
  AH5_RndObjLoad(&Uni->Cow, "cow.object");
} /* End of 'AH5_UnitInit' function */

/* Cow drawing unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_COW *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitClose( ah5UNIT_COW *Uni, ah5ANIM *Ani )
{
  AH5_RndObjFree(&Uni->Cow);
} /* End of 'AH5_UnitClose' function */

/* Cow drawing unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_COW *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitResponse( ah5UNIT_COW *Uni, ah5ANIM *Ani )
{
} /* End of 'AH5_UnitResponse' function */

/* Cow drawing unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_COW *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitRender( ah5UNIT_COW *Uni, ah5ANIM *Ani )
{
  AH5_RndObjDraw(&Uni->Cow, MatrMulMatr(MatrRotateY(AH5_Anim.Mx / 300.0), MatrRotateX(AH5_Anim.My / 300.0)));
} /* End of 'AH5_UnitRender' function */

/* Cow drawing unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ah5UNIT *) pointer to created unit.
 */
ah5UNIT * AH5_UnitCreateCow( VOID )
{
  ah5UNIT_COW *Uni;

  /* Memory allocation */
  if ((Uni = (ah5UNIT_COW *)AH5_AnimUnitCreate(sizeof(ah5UNIT_COW))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AH5_UnitInit;
  Uni->Close = (VOID *)AH5_UnitClose;
  Uni->Response = (VOID *)AH5_UnitResponse;
  Uni->Render = (VOID *)AH5_UnitRender;
  return (ah5UNIT *)Uni;
} /* End of 'AH5_UnitCreateCow' function */

/* END OF 'U_COW.C' FILE */
