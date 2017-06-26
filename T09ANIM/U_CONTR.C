/* FILE NAME: U_CONTR.C
 * PROGRAMMER: AH5
 * DATE: 10.06.2017
 * PURPOSE: Units base functions.
 */

#include <stdio.h>
#include <math.h>
#include <time.h>

#include "units.h"

/* Animation unit representation type */
typedef struct tagUNIT_CONTROL
{
  AH5_UNIT_BASE_FIELDS;
} ah5UNIT_CONTROL;

FLT px = 0, py = 0, pz = 0, rt = PI / 2, rty = PI / 2, acc = 0;
/* Control unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_CONTROL *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitInit( ah5UNIT_CONTROL *Uni, ah5ANIM *Ani )
{
} /* End of 'AH5_UnitInit' function */

/* Control unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_CONTROL *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitClose( ah5UNIT_CONTROL *Uni, ah5ANIM *Ani )
{
} /* End of 'AH5_UnitClose' function */

/* Control unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_CONTROL *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitResponse( ah5UNIT_CONTROL *Uni, ah5ANIM *Ani )
{
  if (py > 0)
    py -= 0.1;

  if (Ani->KeysClick[VK_ESCAPE])
    AH5_AnimClose();
  else if (Ani->KeysClick['F'])
    AH5_AnimFlipFullScreen();
  else if (Ani->KeysClick['P'])
    AH5_Anim.IsPause = !AH5_Anim.IsPause;
  if (Ani->Keys['W'])
  {
    px += 0.8 * cos(rt);
    pz += 0.8 * sin(rt);
  }
  if (Ani->Keys['A'])
  {
    px += 0.5 * sin(rt);
    pz -= 0.5 * cos(rt);
  }
  if (Ani->Keys['S'])
  {
    px -= 0.8 * cos(rt);
    pz -= 0.8 * sin(rt);
  }
  if (Ani->Keys['D'])
  {
    px -= 0.5 * sin(rt);
    pz += 0.5 * cos(rt);
  }
  if (Ani->Mdx != 0)
    rt += Ani->Mdx / 45.0;
  if (Ani->Mdy != 0 && (rty - Ani->Mdy / 2000.0 > -PI / 2) && (rty - Ani->Mdy / 2000.0 < PI))
    rty -= Ani->Mdy / 2000.0;
  if (Ani->Keys[VK_SPACE] && py == 0)
  {
    acc = 1.1;
  }

  if (py + acc >= 0)
    py = py + acc;
  else
    py = 0;
  if (py != 0)
    acc = acc - 0.05;

  AH5_RndMatrView = MatrView(VecSet(px, py, pz), VecSet(px + cos(rt), py - sin(rty + PI / 2) * 3, pz + sin(rt)), VecSet(0, 1, 0));
} /* End of 'AH5_UnitResponse' function */

/* Control unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ah5UNIT_CONTROL *Uni;
 *   - animation context:
 *       ah5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AH5_UnitRender( ah5UNIT_CONTROL *Uni, ah5ANIM *Ani )
{
  INT len;
  static DBL save_time;
  static CHAR Buf[100];

  if (Ani->GlobalTime - save_time > 1)
  {
    len = sprintf(Buf, "FPS: %.5f, Units: %d, Wheel: %d, "
      "J: %.3f %.3f %.3f %.3f",
      Ani->FPS, Ani->NumOfUnits, Ani->Mz,
      Ani->Mdy, Ani->Jy, Ani->Jz, Ani->Jr);

    SetWindowText(AH5_Anim.hWnd, Buf);
    save_time = Ani->GlobalTime;
  }
} /* End of 'AH5_UnitRender' function */

/* Control unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ah5UNIT *) pointer to created unit.
 */
ah5UNIT * AH5_UnitCreateControl( VOID )
{
  ah5UNIT_CONTROL *Uni;

  /* Memory allocation */
  if ((Uni = (ah5UNIT_CONTROL *)AH5_AnimUnitCreate(sizeof(ah5UNIT_CONTROL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AH5_UnitInit;
  Uni->Close = (VOID *)AH5_UnitClose;
  Uni->Response = (VOID *)AH5_UnitResponse;
  Uni->Render = (VOID *)AH5_UnitRender;
  return (ah5UNIT *)Uni;
} /* End of 'AH5_UnitCreateControl' function */

/* END OF 'U_CONTR.C' FILE */
