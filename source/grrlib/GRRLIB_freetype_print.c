/* 
**  Created by wplaat (www.plaatsoft.nl)
**
**  Copyright (C) 2009
**  ==================
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, version 2.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
**  History:
**   27-11-2009  Created
*/

/******************************************************************************/
/* This is a very rough implementation if freetype using GRRLIB */

#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>

#include <grrlib.h>

#include <ft2build.h> /* I presume you have freetype for the Wii installed */
#include FT_FREETYPE_H

#include "font_ttf.h"

static FT_Library ftLibrary;
static FT_Face ftFace;

void *fontTempLayer=NULL;
void *fontTexture=NULL;

extern  Mtx                  GXmodelView2D;

/* Static function prototypes */
static void BitmapTo4x4RGBA(const unsigned char *src, void *dst, const unsigned int width, const unsigned int height);
static bool BlitGlyph(FT_Bitmap *bitmap, int offset, int top, int color) ;

void GRRLIB_InitFreetype(void) 
{
	unsigned int error = FT_Init_FreeType(&ftLibrary);
	if (error) 
	{
		exit(0);
	}

	error = FT_New_Memory_Face(ftLibrary, font_ttf, font_ttf_size, 0, &ftFace);
	if (error == FT_Err_Unknown_File_Format) 
	{
		exit(0);
	} 
	else if (error) 
	{
		/* Some other error */
		exit(0);
	}
}

void GRRLIB_initTexture(void)
{
   // Clear previous video frame buffer
   if (fontTexture!=NULL) free(fontTexture);

   fontTempLayer = (void*) calloc(1, 640 * 480 * 4);

   if (fontTempLayer == NULL) 
   {
	  /* Oops! Something went wrong! */
	  exit(0);
   }
}

void GRRLIB_Printf2(int x, int y, const char *string, unsigned int fontSize, int color) 
{
	unsigned int error = 0;
	int penX = 0;
	int penY = fontSize;
	FT_GlyphSlot slot = ftFace->glyph;
	FT_UInt glyphIndex = 0;
	FT_UInt previousGlyph = 0;
	FT_Bool hasKerning = FT_HAS_KERNING(ftFace);

    error = FT_Set_Pixel_Sizes(ftFace, 0, fontSize);
	if (error) 
	{
		/* Failed to set the font size to the requested size. 
		 * You probably should set a default size or something. 
		 * I'll leave that up to the reader. */
		 FT_Set_Pixel_Sizes(ftFace, 0, 12);
	}
	
	/* Convert the string to UTF32 */
	size_t length = strlen(string);
	wchar_t *utf32 = (wchar_t*)malloc(length * sizeof(wchar_t)); 
	length = mbstowcs(utf32, string, length);
	
	/* Loop over each character, drawing it on to the 4, until the 
	 * end of the string is reached, or until the pixel width is too wide */
	unsigned int loop = 0;
	for (loop = 0; loop < length; ++loop)
    {
		glyphIndex = FT_Get_Char_Index(ftFace, utf32[ loop ]);
		
		/* To the best of my knowledge, none of the other freetype 
		 * implementations use kerning, so my method ends up looking
		 * slightly better :) */
		if (hasKerning && previousGlyph && glyphIndex) 
		{
			FT_Vector delta;
			FT_Get_Kerning(ftFace, previousGlyph, glyphIndex, FT_KERNING_DEFAULT, &delta);
			penX += delta.x >> 6;
		}
	
		error = FT_Load_Glyph(ftFace, glyphIndex, FT_LOAD_RENDER);
		if (error)
        {
			/* Whoops, something went wrong trying to load the glyph 
			 * for this character... you should handle this better */
			continue;
		}
	
		if (BlitGlyph(&slot->bitmap, penX + slot->bitmap_left+x, penY - slot->bitmap_top+y, color) == true) 
		{
			/* The glyph was successfully blitted to the buffer, move the pen forwards */
			penX += slot->advance.x >> 6;
			previousGlyph = glyphIndex;
		} 
		else 
		{
			/* BlitGlyph returned false, the line must be full */
			free(utf32);
			return;
		}
	}

	free(utf32);
}

/* Returns true if the character was draw on to the buffer, false if otherwise */
bool BlitGlyph(FT_Bitmap *bitmap, int offset, int top, int color) 
{
	int bitmapWidth = bitmap->width;
	int bitmapHeight = bitmap->rows;

	if (offset + bitmapWidth > 640) 
	{
		/* Drawing this character would over run the buffer, so don't draw it */
		return false;
	}

	/* Draw the glyph onto the buffer, blitting from the bottom up */
	/* CREDIT: Derived from a function by DragonMinded */
	unsigned char *p = fontTempLayer;
	unsigned int y = 0;
	for (y = 0; y < bitmapHeight; ++y) 
	{
		int sywidth = y * bitmapWidth;
		int dywidth = (y + top) * 640;

		unsigned int column = 0;
		for (column = 0; column < bitmapWidth; ++column)
        {
			unsigned int srcloc = column + sywidth;
			unsigned int dstloc = ((column + offset) + dywidth) << 2;
			
			/* Copy the alpha value for this pixel into the texture buffer */
			p[ dstloc + 0 ] = (color & 0xff);
			p[ dstloc + 1 ] = ((color >> 8) & 0xff);
			p[ dstloc + 2 ] = ((color >> 16) & 0xff);
			p[ dstloc + 3 ] = (bitmap->buffer[ srcloc ]);
		}
	}
	
	return true;
}

/* Render the text string to a 4x4RGBA texture, return a pointer to this texture */
void* GRRLIB_GetTexture(void) 
{
	/* Create a new buffer, this time to hold the final texture 
	 * in a format suitable for the Wii */
	fontTexture = memalign(32, 640 * 480 * 4);

	/* Convert the RGBA temp buffer to a format usuable by GX */
	BitmapTo4x4RGBA(fontTempLayer, fontTexture, 640, 480);
	DCFlushRange(fontTexture, 640 * 480 * 4);

	/* The temp buffer is no longer required */
	free(fontTempLayer);

	return fontTexture;
}

void BitmapTo4x4RGBA(const unsigned char *src, void *dst, const unsigned int width, const unsigned int height)
{
	unsigned int block = 0;
	unsigned int i = 0;
	unsigned int c = 0;
	unsigned int ar = 0;
	unsigned int gb = 0;
	unsigned char *p = (unsigned char*)dst;

	for (block = 0; block < height; block += 4) {
		for (i = 0; i < width; i += 4) {
			/* Alpha and Red */
			for (c = 0; c < 4; ++c) {
				for (ar = 0; ar < 4; ++ar) {
					/* Alpha pixels */
					*p++ = src[(((i + ar) + ((block + c) * width)) * 4) + 3];
					/* Red pixels */	
					*p++ = src[((i + ar) + ((block + c) * width)) * 4];
				}
			}
			
			/* Green and Blue */
			for (c = 0; c < 4; ++c) {
				for (gb = 0; gb < 4; ++gb) {
					/* Green pixels */
					*p++ = src[(((i + gb) + ((block + c) * width)) * 4) + 1];
					/* Blue pixels */
					*p++ = src[(((i + gb) + ((block + c) * width)) * 4) + 2];
				}
			}
		} /* i */
	} /* block */
}

void GRRLIB_DrawImg2(f32 xpos, f32 ypos, u8 data[], float degrees, float scaleX, f32 scaleY, u8 alpha )
{
   GXTexObj texObj;
   u16 width=640;
   u16 height=480;
	
	GX_InitTexObj(&texObj, data, width, height, GX_TF_RGBA8,GX_CLAMP, GX_CLAMP,GX_FALSE);
	//GX_InitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
	GX_LoadTexObj(&texObj, GX_TEXMAP0);

	GX_SetTevOp (GX_TEVSTAGE0, GX_MODULATE);
  	GX_SetVtxDesc (GX_VA_TEX0, GX_DIRECT);

	Mtx m,m1,m2, mv;
	width *=.5;
	height*=.5;
	guMtxIdentity (m1);
	guMtxScaleApply(m1,m1,scaleX,scaleY,1.0);
	guVector axis =(guVector) {0 , 0, 1 };
	guMtxRotAxisDeg (m2, &axis, degrees);
	guMtxConcat(m2,m1,m);

	guMtxTransApply(m,m, xpos+width,ypos+height,0);
	guMtxConcat (GXmodelView2D, m, mv);
	GX_LoadPosMtxImm (mv, GX_PNMTX0);
	
	GX_Begin(GX_QUADS, GX_VTXFMT0,4);
  	GX_Position3f32(-width, -height,  0);
  	GX_Color4u8(0xFF,0xFF,0xFF,alpha);
  	GX_TexCoord2f32(0, 0);
  
  	GX_Position3f32(width, -height,  0);
 	GX_Color4u8(0xFF,0xFF,0xFF,alpha);
  	GX_TexCoord2f32(1, 0);
  
  	GX_Position3f32(width, height,  0);
	GX_Color4u8(0xFF,0xFF,0xFF,alpha);
  	GX_TexCoord2f32(1, 1);
  
  	GX_Position3f32(-width, height,  0);
	GX_Color4u8(0xFF,0xFF,0xFF,alpha);
  	GX_TexCoord2f32(0, 1);
	GX_End();
	GX_LoadPosMtxImm (GXmodelView2D, GX_PNMTX0);

	GX_SetTevOp (GX_TEVSTAGE0, GX_PASSCLR);
  	GX_SetVtxDesc (GX_VA_TEX0, GX_NONE);

}

