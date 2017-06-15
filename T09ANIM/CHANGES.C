ANIM.C:
AnimInit:
  VG4_RndProgId = VG4_RndShaderLoad("A");

AnimClose:
  VG4_RndShaderFree(VG4_RndProgId);

AnimRender:
  static DBL ShdTime;
  . . .
  /*** Update shader ***/
  if (VG4_Anim.GlobalTime - ShdTime > 2)
  {
    VG4_RndShaderFree(VG4_RndProgId);
    VG4_RndProgId = VG4_RndShaderLoad("A");
    ShdTime = VG4_Anim.GlobalTime;
  }
  . . .

RENDER.C/H
 . . .
/* Current shader */
UINT
  VG4_RndProgId;    /* Shader program identifier */
