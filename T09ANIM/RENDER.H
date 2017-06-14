/* FILE NAME: RENDER.H
 * PROGRAMMER: AH5
 * DATE: 10.06.2017
 * PURPOSE: Base rendering system module.
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#define GLEW_STATIC
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "def.h"

/* Project parameters */
extern DBL
  AH5_RndProjFarClip,      
  AH5_RndProjDist, /* Distance from viewer to project plane */
  AH5_RndProjSize; /* Prohect plane inner size */

extern MATR
  AH5_RndMatrView,
  AH5_RndMatrProj; 

/* Rendering system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AH5_RndInit( VOID );

/* Project parameters adjust function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AH5_RndSetProj( VOID );

/***
 * Object handle
 ***/

/* Object description type */
typedef struct tagah5OBJ3D
{
  VEC *V;      /* Vertex array */
  INT NumOfV;  /* Vertex array size */
  INT (*F)[3]; /* Facets array (point indices) */
  INT NumOfF;  /* Facets array size */
} ah5OBJ3D;

/* Object free memory function.
 * ARGUMENTS:
 *   - object pointer:
 *       ah5OBJ3D *Obj;
 *   - model *.OBJ file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL AH5_RndObjLoad( ah5OBJ3D *Obj, CHAR *FileName );

/* Object free memory function.
 * ARGUMENTS:
 *   - object pointer:
 *       ah5OBJ3D *Obj;
 * RETURNS: None.
 */
VOID AH5_RndObjFree( ah5OBJ3D *Obj );

/* Object drawing function.
 * ARGUMENTS:
 *   - object pointer:
 *       ah5OBJ3D *Obj;
 *   - world coordinate system transform matrix:
 *       MATR M;
 * RETURNS: None.
 */
VOID AH5_RndObjDraw( ah5OBJ3D *Obj, MATR M );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
