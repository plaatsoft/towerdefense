/*===========================================
        GRRLIB (GX version) 3.0.1 alpha
        Code     : NoNameNo
        GX hints : RedShade
===========================================*/

#include "GRRLIB.h"
#include "font_ttf.h"

/******************************************************************************/
/**** FREETYPE START ****/
/* This is a very rough implementation if freetype using GRRLIB */

#include <ft2build.h> /* I presume you have freetype for the Wii installed */
#include FT_FREETYPE_H

static FT_Library ftLibrary;
static FT_Face ftFace;

void *fontTempLayer=NULL;
void *fontTexture=NULL;

/* Static function prototypes */
static void BitmapTo4x4RGBA(const unsigned char *src, void *dst, const unsigned int width, const unsigned int height);
static bool BlitGlyph(FT_Bitmap *bitmap, int offset, int top, int color) ;

/**
 * Fade in
 * @param width     Texture width.
 * @param height Texture height.
 * @param data   Texture.
 * @param scaleX Texture X scale.
 * @param scaleY Texture Y scale.
 * @param speed  Fade speed (1 is the normal speed, 2 is two time the normal speed, etc).
 */
void GRRLIB_DrawImg_FadeIn(int xpos, int ypos, u16 width, u16 height, u8 data[], float scaleX, f32 scaleY, u16 speed)
{
    int alpha;

    for(alpha = 0; alpha < 255; alpha += speed)
    {
        GRRLIB_DrawImg(xpos, ypos, width, height, data, 0, scaleX, scaleY, alpha);
        GRRLIB_Render();
    }
}


/**
 * Fade out
 * @param width     Texture width.
 * @param height Texture height.
 * @param data   Texture.
 * @param scaleX Texture X scale.
 * @param scaleY Texture Y scale.
 * @param speed  Fade speed (1 is the normal speed, 2 is two time the normal speed, etc).
 */
void GRRLIB_DrawImg_FadeOut(int xpos, int ypos, u16 width, u16 height, u8 data[], float scaleX, f32 scaleY, u16 speed)
{
    int alpha;

    for(alpha = 255; alpha > 0; alpha -= speed)
    {
        GRRLIB_DrawImg(xpos, ypos, width, height, data, 0, scaleX, scaleY, alpha);
        GRRLIB_Render();
    }
}

/**
 * Make a snapshot of the sreen in a texture.
 * @return A texture representing the screen.
 */
extern u8 *GRRLIB_ScreenCap() 
{
    u8 *my_texture;

    GX_SetTexCopySrc(0, 0, 640, 480);
    GX_SetTexCopyDst(640, 480, GX_TF_RGBA8, GX_FALSE);
    my_texture = (u8 *) memalign(32, 640 * 480 * 4); 	
    GX_CopyTex(my_texture, GX_FALSE);
    GX_PixModeSync();
    DCFlushRange(my_texture, 640 * 480 * 4);
    return my_texture;

}

extern void GRRLIB_InitFreetype(void) 
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

extern void GRRLIB_initTexture(void)
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

extern void GRRLIB_Printf2(int x, int y, const char *string, unsigned int fontSize, int color) 
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
static bool BlitGlyph(FT_Bitmap *bitmap, int offset, int top, int color) 
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
	unsigned char *p =  (unsigned char *) fontTempLayer;
	unsigned int y = 0;
	for (y = 0; y < (unsigned int) bitmapHeight; ++y) 
	{
		int sywidth = y * bitmapWidth;
		int dywidth = (y + top) * 640;

		unsigned int column = 0;
		for (column = 0; column < (unsigned int) bitmapWidth; ++column)
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
extern void *GRRLIB_GetTexture(void) 
{
	/* Create a new buffer, this time to hold the final texture 
	 * in a format suitable for the Wii */
	fontTexture = memalign(32, 640 * 480 * 4);

	/* Convert the RGBA temp buffer to a format usuable by GX */
	BitmapTo4x4RGBA((const unsigned char*) fontTempLayer, fontTexture, 640, 480);
	DCFlushRange(fontTexture, 640 * 480 * 4);

	/* The temp buffer is no longer required */
	free(fontTempLayer);

	return fontTexture;
}

static void BitmapTo4x4RGBA(const unsigned char *src, void *dst, const unsigned int width, const unsigned int height)
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

/**** FREETYPE END ****/
/******************************************************************************/

#define DEFAULT_FIFO_SIZE (256 * 1024)

 u32 fb=0;
 static void *xfb[2] = { NULL, NULL};
 GXRModeObj *rmode;
 void *gp_fifo = NULL;


void GRRLIB_FillScreen(u32 color){
	GRRLIB_Rectangle(-40, -40, 680,520, color, 1);
}

void GRRLIB_Plot(f32 x,f32 y, u32 color){
   Vector  v[]={{x,y,0.0f}};
   GXColor c[]={GRRLIB_Splitu32(color)};
	
	GRRLIB_NPlot(v,c,1);
}
void GRRLIB_NPlot(Vector v[],GXColor c[],long n){
	GRRLIB_GXEngine(v,c,n,GX_POINTS);
}

void GRRLIB_Line(f32 x1, f32 y1, f32 x2, f32 y2, u32 color){
   Vector  v[]={{x1,y1,0.0f},{x2,y2,0.0f}};
   GXColor col = GRRLIB_Splitu32(color);
   GXColor c[]={col,col};

	GRRLIB_NGone(v,c,2);
}

void GRRLIB_Rectangle(f32 x, f32 y, f32 width, f32 height, u32 color, u8 filled){
   Vector  v[]={{x,y,0.0f},{x+width,y,0.0f},{x+width,y+height,0.0f},{x,y+height,0.0f},{x,y,0.0f}};
   GXColor col = GRRLIB_Splitu32(color);
   GXColor c[]={col,col,col,col,col};

	if(!filled){
		GRRLIB_NGone(v,c,5);
	}
	else{
		GRRLIB_NGoneFilled(v,c,4);
	}
}
void GRRLIB_NGone(Vector v[],GXColor c[],long n){
	GRRLIB_GXEngine(v,c,n,GX_LINESTRIP);
}
void GRRLIB_NGoneFilled(Vector v[],GXColor c[],long n){
	GRRLIB_GXEngine(v,c,n,GX_TRIANGLEFAN);
}




u8 * GRRLIB_LoadTexture(const unsigned char my_png[]) {
   PNGUPROP imgProp;
   IMGCTX ctx;
   u8 *my_texture;

   	ctx = PNGU_SelectImageFromBuffer(my_png);
        PNGU_GetImageProperties (ctx, &imgProp);
        my_texture = (u8 *) memalign (32, imgProp.imgWidth * imgProp.imgHeight * 4);
        PNGU_DecodeTo4x4RGBA8 (ctx, imgProp.imgWidth, imgProp.imgHeight, my_texture, 255);
        PNGU_ReleaseImageContext (ctx);
        DCFlushRange (my_texture, imgProp.imgWidth * imgProp.imgHeight * 4);
	return my_texture;
}

void GRRLIB_DrawImg(f32 xpos, f32 ypos, u16 width, u16 height, u8 data[], float degrees, float scaleX, f32 scaleY, u8 alpha ){
   GXTexObj texObj;

	
	GX_InitTexObj(&texObj, data, width,height, GX_TF_RGBA8,GX_CLAMP, GX_CLAMP,GX_FALSE);
	//GX_InitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
	GX_LoadTexObj(&texObj, GX_TEXMAP0);

	GX_SetTevOp (GX_TEVSTAGE0, GX_MODULATE);
  	GX_SetVtxDesc (GX_VA_TEX0, GX_DIRECT);

	Mtx m,m1,m2, mv;
	width *=.5;
	height*=.5;
	guMtxIdentity (m1);
	guMtxScaleApply(m1,m1,scaleX,scaleY,1.0);
	Vector axis =(Vector) {0 , 0, 1 };
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

void GRRLIB_DrawTile(f32 xpos, f32 ypos, u16 width, u16 height, u8 data[], float degrees, float scaleX, f32 scaleY, u8 alpha, f32 frame,f32 maxframe ){
GXTexObj texObj;
f32 s1= frame/maxframe;
f32 s2= (frame+1)/maxframe;
f32 t1=0;
f32 t2=1;
	
	GX_InitTexObj(&texObj, data, width*maxframe,height, GX_TF_RGBA8,GX_CLAMP, GX_CLAMP,GX_FALSE);
	GX_InitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
	GX_LoadTexObj(&texObj, GX_TEXMAP0);

	GX_SetTevOp (GX_TEVSTAGE0, GX_MODULATE);
  	GX_SetVtxDesc (GX_VA_TEX0, GX_DIRECT);

	Mtx m,m1,m2, mv;
	width *=.5;
	height*=.5;
	guMtxIdentity (m1);
	guMtxScaleApply(m1,m1,scaleX,scaleY,1.0);
	Vector axis =(Vector) {0 , 0, 1 };
	guMtxRotAxisDeg (m2, &axis, degrees);
	guMtxConcat(m2,m1,m);
	guMtxTransApply(m,m, xpos+width,ypos+height,0);
	guMtxConcat (GXmodelView2D, m, mv);
	GX_LoadPosMtxImm (mv, GX_PNMTX0);
	GX_Begin(GX_QUADS, GX_VTXFMT0,4);
  	GX_Position3f32(-width, -height,  0);
  	GX_Color4u8(0xFF,0xFF,0xFF,alpha);
  	GX_TexCoord2f32(s1, t1);
  
  	GX_Position3f32(width, -height,  0);
 	GX_Color4u8(0xFF,0xFF,0xFF,alpha);
  	GX_TexCoord2f32(s2, t1);
  
  	GX_Position3f32(width, height,  0);
	GX_Color4u8(0xFF,0xFF,0xFF,alpha);
  	GX_TexCoord2f32(s2, t2);
  
  	GX_Position3f32(-width, height,  0);
	GX_Color4u8(0xFF,0xFF,0xFF,alpha);
  	GX_TexCoord2f32(s1, t2);
	GX_End();
	GX_LoadPosMtxImm (GXmodelView2D, GX_PNMTX0);

	GX_SetTevOp (GX_TEVSTAGE0, GX_PASSCLR);
  	GX_SetVtxDesc (GX_VA_TEX0, GX_NONE);

}

void GRRLIB_DrawChar(f32 xpos, f32 ypos, u16 width, u16 height, u8 data[], float degrees, float scaleX, f32 scaleY, f32 frame,f32 maxframe, GXColor c ){
GXTexObj texObj;
f32 s1= frame/maxframe;
f32 s2= (frame+1)/maxframe;
f32 t1=0;
f32 t2=1;
	
	GX_InitTexObj(&texObj, data, width*maxframe,height, GX_TF_RGBA8,GX_CLAMP, GX_CLAMP,GX_FALSE);
	GX_InitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
	GX_LoadTexObj(&texObj, GX_TEXMAP0);

	GX_SetTevOp (GX_TEVSTAGE0, GX_MODULATE);
  	GX_SetVtxDesc (GX_VA_TEX0, GX_DIRECT);

	Mtx m,m1,m2, mv;
	width *=.5;
	height*=.5;
	guMtxIdentity (m1);
	guMtxScaleApply(m1,m1,scaleX,scaleY,1.0);
	Vector axis =(Vector) {0 , 0, 1 };
	guMtxRotAxisDeg (m2, &axis, degrees);
	guMtxConcat(m2,m1,m);
	guMtxTransApply(m,m, xpos+width,ypos+height,0);
	guMtxConcat (GXmodelView2D, m, mv);
	GX_LoadPosMtxImm (mv, GX_PNMTX0);
	GX_Begin(GX_QUADS, GX_VTXFMT0,4);
  	GX_Position3f32(-width, -height,  0);
  	GX_Color4u8(c.r,c.g,c.b,c.a);
  	GX_TexCoord2f32(s1, t1);
  
  	GX_Position3f32(width, -height,  0);
 	GX_Color4u8(c.r,c.g,c.b,c.a);
  	GX_TexCoord2f32(s2, t1);
  
  	GX_Position3f32(width, height,  0);
	GX_Color4u8(c.r,c.g,c.b,c.a);
  	GX_TexCoord2f32(s2, t2);
  
  	GX_Position3f32(-width, height,  0);
	GX_Color4u8(c.r,c.g,c.b,c.a);
  	GX_TexCoord2f32(s1, t2);
	GX_End();
	GX_LoadPosMtxImm (GXmodelView2D, GX_PNMTX0);

	GX_SetTevOp (GX_TEVSTAGE0, GX_PASSCLR);
  	GX_SetVtxDesc (GX_VA_TEX0, GX_NONE);

}

void GRRLIB_Printf(f32 xpos, f32 ypos, u8 data[], u32 color, f32 zoom, char *text,...){
int i ;
char tmp[1024];
int size=0;

va_list argp;
va_start(argp, text);
vsprintf(tmp, text, argp);
va_end(argp);

size = strlen(tmp);
GXColor col = GRRLIB_Splitu32(color);
	for(i=0;i<(int) strlen(tmp);i++){
		u8 c = tmp[i];
		GRRLIB_DrawChar(xpos+i*8*zoom, ypos, 8, 8, data, 0, zoom, zoom, c,128, col );
	}
}

void GRRLIB_GXEngine(Vector v[], GXColor c[], long n,u8 fmt){
   int i=0;	

	GX_Begin(fmt, GX_VTXFMT0,n);
	for(i=0;i<n;i++){
  		GX_Position3f32(v[i].x, v[i].y,  v[i].z);
  		GX_Color4u8(c[i].r, c[i].g, c[i].b, c[i].a);
  	}
	GX_End();
}

GXColor GRRLIB_Splitu32(u32 color){
   u8 a,r,g,b;

	a = (color >> 24) & 0xFF; 
	r = (color >> 16) & 0xFF; 
	g = (color >> 8) & 0xFF; 
	b = (color) & 0xFF; 

	return (GXColor){r,g,b,a};
}




//********************************************************************************************
void GRRLIB_InitVideo () {

	rmode = VIDEO_GetPreferredMode(NULL);
	VIDEO_Configure (rmode);
	xfb[0] = (u32 *)MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	xfb[1] = (u32 *)MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	VIDEO_SetNextFramebuffer(xfb[fb]);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();


	gp_fifo = (u8 *) memalign(32,DEFAULT_FIFO_SIZE);
}

void GRRLIB_Start(){
   
   f32 yscale;
   u32 xfbHeight;
   Mtx perspective;

	GX_Init (gp_fifo, DEFAULT_FIFO_SIZE);

	// clears the bg to color and clears the z buffer
	GXColor background = { 0, 0, 0, 0xff };
	GX_SetCopyClear (background, 0x00ffffff);

	// other gx setup
	yscale = GX_GetYScaleFactor(rmode->efbHeight,rmode->xfbHeight);
	xfbHeight = GX_SetDispCopyYScale(yscale);
	GX_SetScissor(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopySrc(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopyDst(rmode->fbWidth,xfbHeight);
	GX_SetCopyFilter(rmode->aa,rmode->sample_pattern,GX_TRUE,rmode->vfilter);
	GX_SetFieldMode(rmode->field_rendering,((rmode->viHeight==2*rmode->xfbHeight)?GX_ENABLE:GX_DISABLE));

	if (rmode->aa)
		GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
	else
		GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);

	GX_SetDispCopyGamma(GX_GM_1_0);
 

	// setup the vertex descriptor
	// tells the flipper to expect direct data
	GX_ClearVtxDesc();
		GX_InvVtxCache ();
		GX_InvalidateTexAll();

	GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc (GX_VA_CLR0, GX_DIRECT);


		GX_SetVtxAttrFmt (GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
		GX_SetVtxAttrFmt (GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
		GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
		GX_SetZMode (GX_FALSE, GX_LEQUAL, GX_TRUE);

	GX_SetNumChans(1);
	GX_SetNumTexGens(1);
	GX_SetTevOp (GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

	guMtxIdentity(GXmodelView2D);
	guMtxTransApply (GXmodelView2D, GXmodelView2D, 0.0F, 0.0F, -50.0F);
	GX_LoadPosMtxImm(GXmodelView2D,GX_PNMTX0);

	guOrtho(perspective,0,479,0,639,0,300);
	GX_LoadProjectionMtx(perspective, GX_ORTHOGRAPHIC);

	GX_SetViewport(0,0,rmode->fbWidth,rmode->efbHeight,0,1);
	GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GX_SetAlphaUpdate(GX_TRUE);
	
	GX_SetCullMode(GX_CULL_NONE);
}

void GRRLIB_Render () {
        GX_DrawDone ();

	fb ^= 1;		// flip framebuffer
	GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	GX_SetColorUpdate(GX_TRUE);
	GX_CopyDisp(xfb[fb],GX_TRUE);
	VIDEO_SetNextFramebuffer(xfb[fb]);
 	VIDEO_Flush();
 	VIDEO_WaitVSync();

}

