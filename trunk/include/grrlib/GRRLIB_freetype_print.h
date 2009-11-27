/**** WVDP: FREETYPE START ****/
extern void GRRLIB_InitFreetype();
extern void GRRLIB_initTexture(void);
extern void GRRLIB_Printf2(int x, int y, const char *string, unsigned int fontSize, int color); 
extern void* GRRLIB_GetTexture(void);
inline void GRRLIB_DrawImg2(f32 xpos, f32 ypos, u8 data[], float degrees, float scaleX, f32 scaleY, u8 alpha );
/**** WVDP: FREETYPE END ****/
