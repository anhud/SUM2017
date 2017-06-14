/* FILE NAME: RENDER.C
 * PROGRAMMER: AH5
 * DATE: 10.06.2017
 * PURPOSE: Base rendering system module.
 */

#include "anim.h"

/* Project parameters */
DBL
  AH5_RndProjFarClip,       /* no */
  AH5_RndProjDist, /* Distance from viewer to project plane */
  AH5_RndProjSize; /* Prohect plane inner size */

MATR
  AH5_RndMatrView, /* Viewer matrix */
  AH5_RndMatrProj;

/* Rendering system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AH5_RndInit( VOID )
{
  AH5_RndProjFarClip = 1000;
  AH5_RndProjDist = 1;
  AH5_RndProjSize = 1;

  AH5_RndMatrView = MatrView(VecSet1(23), VecSet1(0), VecSet(0, 1, 0));
} /* End of 'AH5_RndInit' function */

/* Project parameters adjust function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AH5_RndSetProj( VOID )
{
  DBL rx = AH5_RndProjSize / 2, ry = AH5_RndProjSize / 2;

  if (AH5_Anim.W > AH5_Anim.H)
    rx *= (DBL)AH5_Anim.W / AH5_Anim.H;
  else
    ry *= (DBL)AH5_Anim.H / AH5_Anim.W;

  AH5_RndMatrProj = MatrFrustum(-rx, rx, -ry, ry, AH5_RndProjDist, AH5_RndProjFarClip);
} /* End of 'AH5_RndSetProj' function */

/* END OF 'RENDER.C' FILE */
