/* FILE NAME: MATERIAL.C
 * PROGRAMMER: AH5
 * DATE: 17.06.2017
 * PURPOSE: Material (texture, shader store) handle module.
 */

#include <string.h>

#include "anim.h"

/***
 * Resource storages
 ***/

/* Materials table */
ah5MATERIAL AH5_RndMaterials[AH5_RES_TABLE_SIZE];
INT AH5_RndNumOfMaterials;

/* Textures table */
ah5TEXTURE AH5_RndTextures[AH5_RES_TABLE_SIZE];
INT AH5_RndNumOfTextures;

/* Shaders table */
ah5SHADER AH5_RndShaders[AH5_RES_TABLE_SIZE];
INT AH5_RndNumOfShaders;

/* Resourcse initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AH5_RndResInit( VOID )
{
  ah5MATERIAL def_mtl =
  {
    "Default material",
    {0.1, 0.1, 0.1}, {0.9, 0.9, 0.9}, {0.3, 0.3, 0.3}, 30,
    1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    "", 0
  };

  memset(AH5_RndMaterials, 0, sizeof(AH5_RndMaterials));
  memset(AH5_RndTextures, 0, sizeof(AH5_RndTextures));
  memset(AH5_RndShaders, 0, sizeof(AH5_RndShaders));
  AH5_RndNumOfMaterials = 0;
  AH5_RndNumOfTextures = 0;
  AH5_RndNumOfShaders = 0;

  AH5_RndShaderAdd("SHADERS\\DEFAULT");
  strcpy(def_mtl.ShaderStr, "SHADERS\\DEFAULT");
  AH5_RndMaterialAdd(&def_mtl);
} /* End of 'AH5_RndResInit' function */

/* Resourcse deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AH5_RndResClose( VOID )
{
  INT i;

  /* Delete shaders */
  for (i = 0; i < AH5_RndNumOfShaders; i++)
    AH5_RndShaderFree(AH5_RndShaders[i].ProgId);
  memset(AH5_RndShaders, 0, sizeof(AH5_RndShaders));
  AH5_RndNumOfShaders = 0;

  /* Delete textures */
  for (i = 0; i < AH5_RndNumOfTextures; i++)
    glDeleteTextures(1, &AH5_RndTextures[i].TexId);
  memset(AH5_RndTextures, 0, sizeof(AH5_RndTextures));
  AH5_RndNumOfTextures = 0;

  /* Remove materials */
  memset(AH5_RndMaterials, 0, sizeof(AH5_RndMaterials));
  AH5_RndNumOfMaterials = 0;
} /* End of 'AH5_RndResClose' function */

/* Add shader function.
 * ARGUMENTS:
 *   - shader file name prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader table number.
 */
INT AH5_RndShaderAdd( CHAR *FileNamePrefix )
{
  if (AH5_RndNumOfShaders >= AH5_RES_TABLE_SIZE)
    return 0;
  strncpy(AH5_RndShaders[AH5_RndNumOfShaders].Name, FileNamePrefix,
    AH5_MATERIAL_NAME_SIZE - 1);
  AH5_RndShaders[AH5_RndNumOfShaders].ProgId =
    AH5_RndShaderLoad(FileNamePrefix);
  return AH5_RndNumOfShaders++;
} /* End of 'AH5_RndShaderAdd' function */

/* Add material function.
 * ARGUMENTS:
 *   - material data:
 *       ah5MATERIAL *Mtl;
 * RETURNS:
 *   (INT) material table number.
 */
INT AH5_RndMaterialAdd( ah5MATERIAL *Mtl )
{
  if (AH5_RndNumOfMaterials >= AH5_RES_TABLE_SIZE)
    return 0;
  AH5_RndMaterials[AH5_RndNumOfMaterials] = *Mtl;
  return AH5_RndNumOfMaterials++;
} /* End of 'AH5_RndMaterialAdd' function */

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
INT AH5_RndTextureAdd( CHAR *Name, INT W, INT H, INT Components, VOID *Data )
{
  if (AH5_RndNumOfTextures >= AH5_RES_TABLE_SIZE)
    return -1;
  strncpy(AH5_RndTextures[AH5_RndNumOfTextures].Name, Name,
    AH5_MATERIAL_NAME_SIZE - 1);
  AH5_RndTextures[AH5_RndNumOfTextures].W = W;
  AH5_RndTextures[AH5_RndNumOfTextures].H = H;

  glGenTextures(1, &AH5_RndTextures[AH5_RndNumOfTextures].TexId);
  glBindTexture(GL_TEXTURE_2D, AH5_RndTextures[AH5_RndNumOfTextures].TexId);
  gluBuild2DMipmaps(GL_TEXTURE_2D, Components, W, H,
    Components == 4 ? GL_BGRA_EXT : Components == 3 ? GL_BGR_EXT : GL_LUMINANCE,
    GL_UNSIGNED_BYTE, Data);
  glBindTexture(GL_TEXTURE_2D, 0);

  return AH5_RndNumOfTextures++;
} /* End of 'AH5_RndTextureAdd' function */

/* Material apply function.
 * ARGUMENTS:
 *   - material table number:
 *       INT MtlNo;
 * RETURNS:
 *   (UINT) shader program Id.
 */
UINT AH5_RndMaterialApply( INT MtlNo )
{
  ah5MATERIAL *mtl;
  INT prg, loc, i;

  if (MtlNo < 0 || MtlNo >= AH5_RndNumOfMaterials)
    MtlNo = 0;
  mtl = &AH5_RndMaterials[MtlNo];

  /* Enable shader */
  prg = mtl->Shader;
  if (prg < 0 || prg >= AH5_RndNumOfShaders)
    prg = 0;
  prg = AH5_RndShaders[prg].ProgId;

  glUseProgram(prg);

  /* Illumination coefficients */
  loc = glGetUniformLocation(prg, "Ka");
  if (loc != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  loc = glGetUniformLocation(prg, "Kd");
  if (loc != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  loc = glGetUniformLocation(prg, "Ks");
  if (loc != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  loc = glGetUniformLocation(prg, "Ph");
  if (loc != -1)
    glUniform1f(loc, mtl->Ph);
  loc = glGetUniformLocation(prg, "Trans");
  if (loc != -1)
    glUniform1f(loc, mtl->Trans);

  /* Textures */
  for (i = 0; i < 8; i++)
  {
    CHAR ist[] = "IsTexture0";
    INT t = mtl->Tex[i];

    /* Set texture usage flag */
    ist[9] = '0' + i;
    loc = glGetUniformLocation(prg, ist);
    if (loc != -1)
      glUniform1i(loc, t != -1);

    /* Select texture to sampler */
    if (t != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, AH5_RndTextures[t].TexId);
    }
  }
  return prg;
} /* End of 'AH5_RndMaterialApply' function */

/* END OF 'MATERIAL.C' FILE */
