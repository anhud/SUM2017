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
  HFONT hFont;           /* Using font */
} ah5UNIT_CONTROL;

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
  Uni->hFont = CreateFont(30, 0, 0, 0, FW_BOLD, TRUE, FALSE, FALSE, DEFAULT_CHARSET,
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
    DEFAULT_PITCH | FF_DONTCARE, "Gloucester MT Extra Condensed");
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
  DeleteObject(Uni->hFont);
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
  if (Ani->KeysClick[VK_ESCAPE])
    AH5_AnimClose();
  else if (Ani->KeysClick['F'])
    AH5_AnimFlipFullScreen();
  else if (Ani->KeysClick['P'])
    AH5_Anim.IsPause = !AH5_Anim.IsPause;
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
  HFONT hFontOld = SelectObject(Ani->hDC, Uni->hFont);
  INT len;
  static CHAR Buf[100];

  len = sprintf(Buf, "FPS: %.5f, Units: %d, Wheel: %d, "
    "J: %.3f %.3f %.3f %.3f",
    Ani->FPS, Ani->NumOfUnits, Ani->Mz,
    Ani->Jx, Ani->Jy, Ani->Jz, Ani->Jr);

  SetBkMode(Ani->hDC, TRANSPARENT);
  SetTextColor(Ani->hDC, RGB(0, 0, 0));
  TextOut(Ani->hDC, 2, 2, Buf, len);
  SetTextColor(Ani->hDC, RGB(0, 150, 0));
  TextOut(Ani->hDC, 0, 0, Buf, len);

  SelectObject(Ani->hDC, hFontOld);
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
