#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <ogcsys.h>
#include <gccore.h>
#include <gcmodplay.h> 
#include <wiiuse/wpad.h>
#include <jpeg/jpgogc.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h> 
#include <snd.h>
#include <fat.h>
#include <mxml.h>
#include <sys/dir.h>

#include "GRRLIB.h"
#include "Enemy.h"

// -----------------------------------------------------------
// DEFINES
// -----------------------------------------------------------

#define PROGRAM_NAME	    "TowerDefense"
#define PROGRAM_VERSION     "0.10"
#define RELEASE_DATE        "25-02-2009" 

// Check latest available version 
#define URL1                "http://www.plaatsoft.nl/service/releasenotes5.html"
#define ID1			        "UA-6887062-1"

// Fetch Release notes
#define URL2                "http://www.plaatsoft.nl/service/releasenotes5.html"
#define ID2				    "UA-6887062-1"

// Set Score and get global Highscore
#define URL3                "http://www.plaatsoft.nl/service/score_set.php"
#define ID3				    "UA-6887062-1"

#define URL_TOKEN           " Version "
#define HIGHSCORE_FILENAME  "sd:/apps/TowerDefense/highscore.xml"
#define SETTING_FILENAME    "sd:/apps/TowerDefense/setting.xml"

#define WSP_POINTER_X       200
#define WSP_POINTER_Y       250

#define COLOR_WHITESMOKE    0xFFFFFF
#define COLOR_LIGHTRED      0x3333FF
#define COLOR_DARKBLACK     0x000000

#define MAX_BUTTONS         10
#define MAX_RUMBLE			4
#define MAX_BOARDSIZE 		14
#define MAX_BUBBLES   		(MAX_BOARDSIZE*MAX_BOARDSIZE)
#define MAX_HORZ_PIXELS		640
#define MAX_VERT_PIXELS		480
#define MAX_HIGHSCORES 		50
#define MAX_SETTINGS		10
#define MAX_BEST	 		50
#define MAX_LEVEL    	    7
#define MAX_LEN			    256
#define MAX_ANGLE			360
#define MIN_ALFA			127
#define MAX_ALFA			255
#define MIN_SIZE			1.0
#define MAX_SIZE			1.2
#define MAX_SOUND_VOLUME	10
#define MAX_MUSIC_TRACK     16
#define MAX_LINES		    200
#define MAX_BUFFER_SIZE		8192
#define MAX_IDLE_TIME	    10
#define MAX_POINTER         1
#define EXPLODE_STEP	    4
#define OUT_OF_TIME		    15
#define IR_X_OFFSET         40
#define IR_Y_OFFSET         40
#define SCROLLBAR_x         600
#define SCROLLBAR_Y_MIN     150
#define SCROLLBAR_Y_MAX     310

#define MUSIC_MULTIPLER		5
#define EFFECT_MULTIPLER	20

#define BUTTON_A            (WPAD_BUTTON_A     | WPAD_CLASSIC_BUTTON_A)
#define BUTTON_HOME         (WPAD_BUTTON_HOME  | WPAD_CLASSIC_BUTTON_HOME)
#define BUTTON_1            (WPAD_BUTTON_1     | WPAD_CLASSIC_BUTTON_X)
#define BUTTON_2            (WPAD_BUTTON_2     | WPAD_CLASSIC_BUTTON_Y)

#define BUTTON_UP           (WPAD_BUTTON_UP    | WPAD_CLASSIC_BUTTON_UP)
#define BUTTON_DOWN         (WPAD_BUTTON_DOWN  | WPAD_CLASSIC_BUTTON_DOWN)
#define BUTTON_LEFT         (WPAD_BUTTON_LEFT  | WPAD_CLASSIC_BUTTON_LEFT)
#define BUTTON_RIGHT        (WPAD_BUTTON_RIGHT | WPAD_CLASSIC_BUTTON_RIGHT)

// -----------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------

// -----------------------------------------------------------
// VARIABLES
// -----------------------------------------------------------


// Intro1 Image
extern char     pic1data[];
extern int      pic1length;

// Intro2 Image
extern char     pic2data[];
extern int      pic2length;

// Intro3 Image
extern char     pic3data[];
extern int      pic3length;

// Pointer1 Image
extern char     pic4data[];
extern int      pic4length;

// Enemy1 Image
extern char     pic5data[];
extern int      pic5length;

u32    *frameBuffer[1] = {NULL};
GXRModeObj *rmode2 = NULL;
Mtx     GXmodelView2D;
static u32 *xfb;

// -----------------------------------
// TYPEDEFS
// -----------------------------------

typedef struct 
{
  ir_t    ir;
  int     x;
  int     xOffset;
  int     y;
  int     yOffset;
  int     angle;
  int     rumble;
  u8      *image;
}
pointer;

pointer pointers[MAX_POINTER];

// -----------------------------------
// Game logic
// -----------------------------------


/*void drawIntroScreen(int nr)
{
   boolean flag = true;
   
   switch (nr)
   {
      case 0: drawJpegImage(pic1data, pic1length, 0, 0 );
	          break;
			  
	  case 1: drawJpegImage(pic2data, pic2length, 0, 0 );
	          break;
			  
	  case 2: drawJpegImage(pic3data, pic3length, 0, 0 );
	          break;
   }
		   	
   // Handle buttons events
   while ( flag )
   {
		WPAD_ScanPads(); 
		if (WPAD_ButtonsDown(WPAD_CHAN_0) & BUTTON_A) flag=false; 	
		if (WPAD_ButtonsDown(WPAD_CHAN_1) & BUTTON_A) flag=false; 	
		if (WPAD_ButtonsDown(WPAD_CHAN_2) & BUTTON_A) flag=false; 	
		if (WPAD_ButtonsDown(WPAD_CHAN_3) & BUTTON_A) flag=false; 			
		VIDEO_SetNextFramebuffer(frameBuffer[0]); 
		VIDEO_Flush();
		VIDEO_WaitVSync();
   }
}*/

void Initialise() 
{
    VIDEO_Init();
    WPAD_Init();
 
    rmode2 = VIDEO_GetPreferredMode(NULL);
 
    xfb = (u32*) MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode2));
    console_init(xfb,20,20,rmode2->fbWidth,rmode2->xfbHeight,rmode2->fbWidth*VI_DISPLAY_PIX_SZ);
 
    VIDEO_Configure(rmode2);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if(rmode2->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
}

// -----------------------------------
// main
// -----------------------------------

int main()
{
	int i;
	Initialise();	

	//drawIntroScreen(1);		
	//drawIntroScreen(2);	
	//drawIntroScreen(3);	
  		
    // Init wiimote layer
    WPAD_Init();
    WPAD_SetIdleTimeout(60); // Wiimote is shutdown after 60 seconds of innactivity.
    WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);

    // Init FreeType font engine
	GRRLIB_InitFreetype();

    // Init GRRLib graphics library
    GRRLIB_InitVideo();
    GRRLIB_Start();
    
	// Make screen black
	GRRLIB_FillScreen(0xFFFFFF);
    GRRLIB_Render();
	
    pointers[0].image=GRRLIB_LoadTexture((unsigned char*) pic4data); 
   
	Enemy enemy(100,100,32,32,1,45,255,pic5data);
	
	// Repeat forever
    while( true )
	{				
		enemy.draw();
		enemy.move();
		
        // Init text layer	  
        GRRLIB_initTexture();

        enemy.properties();
		
        // Draw text layer on top of gameboard 
        GRRLIB_DrawImg(0, 0, 640, 480, (u8 *) GRRLIB_GetTexture(), 0, 1.0, 1.0, 255);

		 // Scan for button events
		WPAD_SetVRes(0, 640, 480);
        WPAD_ScanPads();
			
		for (i=0; i<MAX_POINTER; i++)
		{
		  u32 wpaddown = WPAD_ButtonsDown(i);
		
          // Scan for ir events 
		  WPAD_IR(i, &pointers[i].ir); 
		  pointers[i].x=pointers[i].ir.sx-WSP_POINTER_X;
		  pointers[i].xOffset=pointers[i].x+IR_X_OFFSET;
		  pointers[i].y=pointers[i].ir.sy-WSP_POINTER_Y;
		  pointers[i].yOffset=pointers[i].y+IR_Y_OFFSET;
		  pointers[i].angle=pointers[i].ir.angle;
				
		  // Scan for button events
		  if (wpaddown & WPAD_BUTTON_HOME) exit(0);
				
		  if (wpaddown & WPAD_BUTTON_PLUS) 
		  {
		     int value=enemy.getStep();
		     enemy.setStep(++value);
		  }
       				
     	  if (wpaddown & WPAD_BUTTON_MINUS) 
		  {
		     int value=enemy.getStep();
		     enemy.setStep(--value);
		  }
			
       	  // Draw wiimote ir pointer
          GRRLIB_DrawImg( pointers[i].x, pointers[i].y, 96, 96, pointers[i].image, pointers[i].angle, 1, 1, 255 );			 
		}
		
		GRRLIB_Render();
	}
	return 0; 
}
