/*===========================================
        GRRLIB (GX version) 3.0.1 alpha
        Code     : NoNameNo
        GX hints : RedShade
===========================================*/

#ifndef __GXHDR__
#define __GXHDR__
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>

#include "pngu.h"

// Special effects 
extern u8 *GRRLIB_ScreenCap();
void GRRLIB_DrawImg_FadeIn(int xpos, int ypos, u16 width, u16 height, u8 data[], float scaleX, f32 scaleY, u16 speed);
void GRRLIB_DrawImg_FadeOut(int xpos, int ypos, u16 width, u16 height, u8 data[], float scaleX, f32 scaleY, u16 speed);

/**** FREETYPE START ****/
extern void GRRLIB_InitFreetype();
extern void GRRLIB_initTexture(void);
extern void GRRLIB_Printf2(int x, int y, const char *string, unsigned int fontSize, int color); 
extern void *GRRLIB_GetTexture(void);

/**** FREETYPE END ****/

extern Mtx GXmodelView2D;

void GRRLIB_FillScreen(u32 color);

void GRRLIB_Plot(f32 x,f32 y, u32 color);
void GRRLIB_NPlot(Vector v[],GXColor c[],long n);

void GRRLIB_Line(f32 x1, f32 y1, f32 x2, f32 y2, u32 color);

void GRRLIB_Rectangle(f32 x, f32 y, f32 width, f32 height, u32 color, u8 filled);
void GRRLIB_NGone(Vector v[],GXColor c[],long n);
void GRRLIB_NGoneFilled(Vector v[],GXColor c[],long n);


u8 * GRRLIB_LoadTexture(const unsigned char my_png[]);
void GRRLIB_DrawImg(f32 xpos, f32 ypos, u16 width, u16 height, u8 data[], float degrees, float scaleX, f32 scaleY, u8 alphaF );
void GRRLIB_DrawTile(f32 xpos, f32 ypos, u16 width, u16 height, u8 data[], float degrees, float scaleX, f32 scaleY, u8 alpha, f32 frame,f32 maxframe );
void GRRLIB_DrawChar(f32 xpos, f32 ypos, u16 width, u16 height, u8 data[], float degrees, float scaleX, f32 scaleY, f32 frame,f32 maxframe, GXColor c );

void GRRLIB_Printf(f32 xpos, f32 ypos, u8 data[], u32 color, f32 zoom, char* text,...);

GXColor GRRLIB_Splitu32(u32 color);

void GRRLIB_GXEngine(Vector v[], GXColor c[], long count,u8 fmt);


void GRRLIB_InitVideo ();
void GRRLIB_Start();
void GRRLIB_Render ();


#endif
