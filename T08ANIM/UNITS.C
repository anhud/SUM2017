/* FILE NAME: UNITS.C
 * PROGRAMMER: AH5
 * DATE: 09.06.2017
 * PURPOSE: nein
 */

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitInit( ah5UNIT *Uni, ah5ANIM *Ani )
{
} /* End of 'AH5_UnitInit' function */
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitClose( ah5UNIT *Uni, ah5ANIM *Ani )
{
} /* End of 'AH5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitResponse( ah5UNIT *Uni, ah5ANIM *Ani )
{
} /* End of 'AH5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitRender( ah5UNIT *Uni, ah5ANIM *Ani )
{
} /* End of 'AH5_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (ah5UNIT *) pointer to created unit.
 */
ah5UNIT * AH5_AnimUnitCreate( INT Size )
{
  ah5UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(ah5UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* Setup unit methods */
  Uni->Init = AH5_UnitInit;
  Uni->Close = AH5_UnitClose;
  Uni->Response = AH5_UnitResponse;
  Uni->Render = AH5_UnitRender;
  return Uni;
} /* End of 'AH5_AnimUnitCreate' function */