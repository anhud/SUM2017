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

#define AH5_RES_TABLE_SIZE 1000

#define AH5_MATERIAL_NAME_SIZE 300

/* Project parameters */
extern DBL
  AH5_RndProjFarClip,      
  AH5_RndProjDist, /* Distance from viewer to project plane */
  AH5_RndProjSize; /* Prohect plane inner size */

extern MATR
  AH5_RndMatrView,
  AH5_RndMatrProj;

 extern VEC
  AH5_RndLightPos,
  AH5_RndLightColor;


 typedef struct tagah5SHADER
{
  CHAR Name[AH5_MATERIAL_NAME_SIZE]; /* Shader file name prefix */
  UINT ProgId;                       /* Shader program ID */
} ah5SHADER;

/* Texture store representation type */
typedef struct tagah5TEXTURE
{
  CHAR Name[AH5_MATERIAL_NAME_SIZE]; /* Texture file name */
  INT W, H;                          /* Texture image size */
  UINT TexId;                        /* Texture ID */
} ah5TEXTURE;

/* Material store representation type */
typedef struct tagah5MATERIAL
{
  CHAR Name[AH5_MATERIAL_NAME_SIZE]; /* Material name */

  /* Illumination coefficients */ 
  VEC Ka, Kd, Ks;                    /* Ambient, diffuse, specular coefficients */
  FLT Ph;                            /* Phong power coefficient */
  FLT Trans;                         /* Transparency factor */
  INT Tex[8];                        /* Texture references */

  /* Shader string */
  CHAR ShaderStr[AH5_MATERIAL_NAME_SIZE];
  INT Shader;                        /* Texture references */
} ah5MATERIAL;

/* Materials table */
extern ah5MATERIAL AH5_RndMaterials[AH5_RES_TABLE_SIZE];
extern INT AH5_RndNumOfMaterials;

/* Textures table */
extern ah5TEXTURE AH5_RndTextures[AH5_RES_TABLE_SIZE];
extern INT AH5_RndNumOfTextures;

/* Shaders table */
extern ah5SHADER AH5_RndShaders[AH5_RES_TABLE_SIZE];
extern INT AH5_RndNumOfShaders;

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
typedef struct tagah5PRIM
{
  INT NumOfI;
  INT VA, VBuf;
  INT IBuf;
  BOOL IsTrimesh;
  MATR M;
  INT MtlNo;
} ah5PRIM;
typedef struct tagah5VERTEX
{
  VEC P;
  VEC2 T;
  VEC N;
  VEC4 C;
} ah5VERTEX;
typedef struct tagah5OBJ
{
  ah5PRIM *P;
  INT NumOfP;
} ah5OBJ;

/* Object free memory function.
 * ARGUMENTS:
 *   - object pointer:
 *       ah5OBJ *Obj;
 *   - model *.OBJ file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL AH5_RndObjLoad( ah5OBJ *Obj, CHAR *FileName );

/* Object free memory function.
 * ARGUMENTS:
 *   - object pointer:
 *       ah5OBJ *Obj;
 * RETURNS: None.
 */
VOID AH5_RndObjFree( ah5OBJ *Obj );

/* Object drawing function.
 * ARGUMENTS:
 *   - object pointer:
 *       ah5OBJ *Obj;
 *   - world coordinate system transform matrix:
 *       MATR M;
 * RETURNS: None.
 */

VOID AH5_RndObjCreate( ah5OBJ *Obj, INT NumOfP );

VOID AH5_RndObjDraw( ah5OBJ *Obj, MATR M );

VOID AH5_RndPrimCreate( ah5PRIM *Pr, BOOL IsTrimesh, ah5VERTEX *V, INT NumOfV, INT *I, INT NumOfI );

VOID AH5_RndPrimFree( ah5PRIM *Pr );

VOID AH5_RndPrimDraw( ah5PRIM *Pr, MATR M );

BOOL AH5_RndPrimLoad( ah5PRIM *Obj, CHAR *FileName );

VOID AH5_RndTriMeshEvalNormals( ah5VERTEX *V, INT NumOfV, INT *I, INT NumOfI );

VOID AH5_RndGridEvalNormals( ah5VERTEX *V, INT N, INT M );

VOID AH5_RndPrimCreateSphere( ah5PRIM *Pr, VEC C, FLT R, INT N, INT M );

VOID AH5_RndPrimCreatePlane( ah5PRIM *Pr, VEC C, VEC Du, VEC Dv, INT N, INT M );

/* CHAR * AH5_RndShaderLoadTextFile( CHAR *FileName );

VOID AH5_RndShaderLog( CHAR *Stage, CHAR *Text );  */

VOID AH5_RndShaderFree( UINT Prg );

UINT AH5_RndShaderLoad( CHAR *FileNamePrefix );

/* Resourcse initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AH5_RndResInit( VOID );

/* Resourcse deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AH5_RndResClose( VOID );

/* Add shader function.
 * ARGUMENTS:
 *   - shader file name prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader table number.
 */
INT AH5_RndShaderAdd( CHAR *FileNamePrefix );

/* Add material function.
 * ARGUMENTS:
 *   - material data:
 *       ah5MATERIAL *Mtl;
 * RETURNS:
 *   (INT) material table number.
 */
INT AH5_RndMaterialAdd( ah5MATERIAL *Mtl );

/* Add texture function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture image size:
 *       INT W, H;
 *   - texture image pixel number of component:
 *       INT Components;
 *   - texture image pixel color data:
 *       VOID *Data;
 * RETURNS:
 *   (INT) texture table number.
 */
INT AH5_RndTextureAdd( CHAR *Name, INT W, INT H, INT Components, VOID *Data );

/* Material apply function.
 * ARGUMENTS:
 *   - material table number:
 *       INT MtlNo;
 * RETURNS:
 *   (UINT) shader program Id.
 */
UINT AH5_RndMaterialApply( INT MtlNo );



#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
