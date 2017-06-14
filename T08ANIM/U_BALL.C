/* FILE NAME: U_BBALL.C
 * PROGRAMMER: AH5
 * DATE: 09.06.2017
 * PURPOSE: serbia 
 */

#include "units.h"

typedef struct tagUNIT_BALL
{
  AH5_UNIT_BASE_FIELDS;
  VEC Pos;
} ah5UNIT_BALL;

/* Unit ball initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_BALL *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitInit( ah5UNIT_BALL *Uni, ah5ANIM *Ani )
{
  Uni->Pos = VecSet(0, 1, 0);
} /* End of 'AH5_UnitInit' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_BALL *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitRender( ah5UNIT_BALL *Uni, ah5ANIM *Ani )
{
  Ellipse(Ani->hDC, 0, 0, Ani->W / 10, Ani->H / 10);
} /* End of 'AH5_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ah5UNIT *) pointer to created unit.
 */
ah5UNIT * AH5_UnitCreateBall( VOID )
{
  ah5UNIT_BALL *Uni;

  if ((Uni = (ah5UNIT_BALL *)AH5_AnimUnitCreate(sizeof(ah5UNIT_BALL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = AH5_UnitInit;
  Uni->Render = AH5_UnitRender;
  return (ah5UNIT *)Uni;
} /* End of 'AH5_UnitCreateBall' function */