/* FILE NAME: U_DESK.C
 * PROGRAMMER: AH5
 * DATE: 10.06.2017
 * PURPOSE: Units base functions.
 */

#include <stdio.h>
#include <math.h>
#include <time.h>

#include "units.h"

/* Animation unit representation type */
typedef struct tagUNIT_DESK
{
  AH5_UNIT_BASE_FIELDS;
  ah5OBJ Desk; /* Desk model */
} ah5UNIT_DESK;

/* Desk drawing unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_DESK *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitInit( ah5UNIT_DESK *Uni, ah5ANIM *Ani )
{
  AH5_RndObjLoad(&Uni->Desk, "Ayer Writing Desk.obj");
} /* End of 'AH5_UnitInit' function */

/* Desk drawing unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_DESK *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitClose( ah5UNIT_DESK *Uni, ah5ANIM *Ani )
{
  AH5_RndObjFree(&Uni->Desk);
} /* End of 'AH5_UnitClose' function */

/* Desk drawing unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_DESK *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitResponse( ah5UNIT_DESK *Uni, ah5ANIM *Ani )
{
  if (Ani->KeysClick['E'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else if (Ani->KeysClick['R'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
} /* End of 'AH5_UnitResponse' function */

/* Desk drawing unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_DESK *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitRender( ah5UNIT_DESK *Uni, ah5ANIM *Ani )
{
  AH5_RndObjDraw(&Uni->Desk, UnitMatrix);
} /* End of 'AH5_UnitRender' function */

/* Desk drawing unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ah5UNIT *) pointer to created unit.
 */
ah5UNIT * AH5_UnitCreateDesk( VOID )
{
  ah5UNIT_DESK *Uni;

  /* Memory allocation */
  if ((Uni = (ah5UNIT_DESK *)AH5_AnimUnitCreate(sizeof(ah5UNIT_DESK))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AH5_UnitInit;
  Uni->Close = (VOID *)AH5_UnitClose;
  Uni->Response = (VOID *)AH5_UnitResponse;
  Uni->Render = (VOID *)AH5_UnitRender;
  return (ah5UNIT *)Uni;
} /* End of 'AH5_UnitCreateDesk' function */

/* END OF 'U_DESK.C' FILE */
