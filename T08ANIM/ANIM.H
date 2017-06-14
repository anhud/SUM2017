/* FILE NAME: ANIM.H
 * PROGRAMMER: AH5
 * DATE: 09.06.2017
 * PURPOSE: asjhjashfsjkhfashfkajshfjkashfjasf 
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "def.h"
#include "render.h"

#define AH5_MAX_UNITS 50

extern INT AH5_MouseWheel;

typedef struct tagah5ANIM ah5ANIM; 
typedef struct tagah5UNIT ah5UNIT;

struct tagah5ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;
  HBITMAP hBm;
  ah5UNIT *Units[AH5_MAX_UNITS];
  INT NumOfUnits;
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per seond value */
  BOOL
    IsPause;                     /* Pause flag */
  
  BYTE Keys[256];
  BYTE KeysOld[256];
  BYTE KeysClick[256];
  
  INT
    Mx, My, Mz,     /* Absolute coordinates */
    Mdx, Mdy, Mdz;  /* Relative coordinates shift */

  BYTE
    JBut[32],                    /* Joystick button state */
    JButOld[32],                 /* Joystick button old state */
    JButClick[32];               /* Joystick button click info */
  INT JPov;                      /* Joystick point-of-view control [0,1..8] */
  DBL
    Jx, Jy, Jz, Jr;              /* Joystick axes */
};

extern ah5ANIM AH5_Anim;                          

#define AH5_UNIT_BASE_FIELDS                      \
  /* Unit initialization function.                \
   * ARGUMENTS:                                   \
   *   - self-pointer to unit object:             \
   *       ah5UNIT *Uni;                          \
   *   - animation context:                       \
   *       ah5ANIM *Ani;                          \
   * RETURNS: None.                               \
   */                                             \
  VOID (*Init)( ah5UNIT *Uni, ah5ANIM *Ani );     \
                                                  \
  /* Unit deinitialization function.              \
   * ARGUMENTS:                                   \
   *   - self-pointer to unit object:             \
   *       ah5UNIT *Uni;                          \
   *   - animation context:                       \
   *       ah5ANIM *Ani;                          \
   * RETURNS: None.                               \
   */                                             \
  VOID (*Close)( ah5UNIT *Uni, ah5ANIM *Ani );    \
                                                  \
  /* Unit inter frame events handle function.     \
   * ARGUMENTS:                                   \
   *   - self-pointer to unit object:             \
   *       ah5UNIT *Uni;                          \
   *   - animation context:                       \
   *       ah5ANIM *Ani;                          \
   * RETURNS: None.                               \
   */                                             \
  VOID (*Response)( ah5UNIT *Uni, ah5ANIM *Ani ); \
                                                  \
  /* Unit render function.                        \
   * ARGUMENTS:                                   \
   *   - self-pointer to unit object:             \
   *       ah5UNIT *Uni;                          \
   *   - animation context:                       \
   *       ah5ANIM *Ani;                          \
   * RETURNS: None.                               \
   */                                             \
  VOID (*Render)( ah5UNIT *Uni, ah5ANIM *Ani )


struct tagah5UNIT
{
  AH5_UNIT_BASE_FIELDS;
};

VOID AH5_AnimInit( HWND hWnd );
VOID AH5_AnimClose( VOID );
VOID AH5_AnimResize( INT W, INT H );
VOID AH5_AnimCopyFrame( HDC hDC );
VOID AH5_AnimRender( VOID );
VOID AH5_AnimAddUnit( ah5UNIT *Uni );
VOID AH5_AnimFlipFullScreen( VOID );
ah5UNIT * AH5_AnimUnitCreate( INT Size );

#endif