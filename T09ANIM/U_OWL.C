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
typedef struct tagUNIT_OWL
{
  AH5_UNIT_BASE_FIELDS;
  ah5PRIM Owl; /* Cow model */
} ah5UNIT_OWL;

/* Cow drawing unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_COW *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitInit( ah5UNIT_OWL *Uni, ah5ANIM *Ani )
{
  AH5_RndPrimLoad(&Uni->Owl, "s.object");
} /* End of 'AH5_UnitInit' function */

/* Cow drawing unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_COW *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitClose( ah5UNIT_OWL *Uni, ah5ANIM *Ani )
{
  AH5_RndPrimFree(&Uni->Owl);
} /* End of 'AH5_UnitClose' function */

/* Cow drawing unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_COW *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitResponse( ah5UNIT_OWL *Uni, ah5ANIM *Ani )
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
static VOID AH5_UnitRender( ah5UNIT_OWL *Uni, ah5ANIM *Ani )
{
  AH5_RndPrimDraw(&Uni->Owl, MatrMulMatr(MatrMulMatr(UnitMatrix, MatrTranslate(VecSet(sin(AH5_Anim.GlobalTime) * 10, (cos(AH5_Anim.GlobalTime) + 1) * 5, 0))), MatrRotateY((cos(AH5_Anim.GlobalTime) + 1) * 5)));
} /* End of 'AH5_UnitRender' function */

/* Cow drawing unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ah5UNIT *) pointer to created unit.
 */
ah5UNIT * AH5_UnitCreateOwl( VOID )
{
  ah5UNIT_OWL *Uni;

  /* Memory allocation */
  if ((Uni = (ah5UNIT_OWL *)AH5_AnimUnitCreate(sizeof(ah5UNIT_OWL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AH5_UnitInit;
  Uni->Close = (VOID *)AH5_UnitClose;
  Uni->Response = (VOID *)AH5_UnitResponse;
  Uni->Render = (VOID *)AH5_UnitRender;
  return (ah5UNIT *)Uni;
} /* End of 'AH5_UnitCreate not a cow' function */

/* END OF 'U_COW.C' FILE */
