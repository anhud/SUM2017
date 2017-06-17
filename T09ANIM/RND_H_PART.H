/***
 * Material support
 ***/

#define VG4_RES_TABLE_SIZE 1000

#define VG4_MATERIAL_NAME_SIZE 300

/* Shader store representation type */
typedef struct tagvg4SHADER
{
  CHAR Name[VG4_MATERIAL_NAME_SIZE]; /* Shader file name prefix */
  UINT ProgId;                       /* Shader program ID */
} vg4SHADER;

/* Texture store representation type */
typedef struct tagvg4TEXTURE
{
  CHAR Name[VG4_MATERIAL_NAME_SIZE]; /* Texture file name */
  INT W, H;                          /* Texture image size */
  UINT TexId;                        /* Texture ID */
} vg4TEXTURE;

/* Material store representation type */
typedef struct tagvg4MATERIAL
{
  CHAR Name[VG4_MATERIAL_NAME_SIZE]; /* Material name */

  /* Illumination coefficients */ 
  VEC Ka, Kd, Ks;                    /* Ambient, diffuse, specular coefficients */
  FLT Ph;                            /* Phong power coefficient */
  FLT Trans;                         /* Transparency factor */
  INT Tex[8];                        /* Texture references */

  /* Shader string */
  CHAR ShaderStr[VG4_MATERIAL_NAME_SIZE];
  INT Shader;                        /* Texture references */
} vg4MATERIAL;

/* Materials table */
extern vg4MATERIAL VG4_RndMaterials[VG4_RES_TABLE_SIZE];
extern INT VG4_RndNumOfMaterials;

/* Textures table */
extern vg4TEXTURE VG4_RndTextures[VG4_RES_TABLE_SIZE];
extern INT VG4_RndNumOfTextures;

/* Shaders table */
extern vg4SHADER VG4_RndShaders[VG4_RES_TABLE_SIZE];
extern INT VG4_RndNumOfShaders;

/* Resourcse initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG4_RndResInit( VOID );

/* Resourcse deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG4_RndResClose( VOID );

/* Add shader function.
 * ARGUMENTS:
 *   - shader file name prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader table number.
 */
INT VG4_RndShaderAdd( CHAR *FileNamePrefix );

/* Add material function.
 * ARGUMENTS:
 *   - material data:
 *       vg4MATERIAL *Mtl;
 * RETURNS:
 *   (INT) material table number.
 */
INT VG4_RndMaterialAdd( vg4MATERIAL *Mtl );

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
INT VG4_RndTextureAdd( CHAR *Name, INT W, INT H, INT Components, VOID *Data );

/* Material apply function.
 * ARGUMENTS:
 *   - material table number:
 *       INT MtlNo;
 * RETURNS:
 *   (UINT) shader program Id.
 */
UINT VG4_RndMaterialApply( INT MtlNo );

