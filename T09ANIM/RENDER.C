/* FILE NAME: RENDER.C
 * PROGRAMMER: AH5
 * DATE: 10.06.2017
 * PURPOSE: Base rendering system module.
 */

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32s")

#include "anim.h"

/* Project parameters */
DBL
  AH5_RndProjFarClip,       /* no */
  AH5_RndProjDist, /* Distance from viewer to project plane */
  AH5_RndProjSize; /* Prohect plane inner size */

MATR
  AH5_RndMatrView, /* Viewer matrix */
  AH5_RndMatrProj;

VEC
  AH5_RndLightPos,
  AH5_RndLightColor;

/* Rendering system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AH5_RndInit( VOID )
{
  AH5_RndProjFarClip = 1000;
  AH5_RndProjDist = 1;
  AH5_RndProjSize = 1;

  AH5_RndResInit();
  AH5_RndMatrView = MatrView(VecSet(20, AH5_Anim.Mz / 60.0, 20), VecSet1(0), VecSet(0, 1, 0));

  AH5_RndLightPos = VecSet(2, -17, 2);
  AH5_RndLightColor = VecSet(0.85, 1, 0.87);

  glEnable(GL_DEPTH_TEST);
  glClearColor(0.1, 0.1, 0.2, 1);
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

VOID AH5_RndClose( VOID )
{
  AH5_RndResClose();
}

/* END OF 'RENDER.C' FILE */
