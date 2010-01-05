/*  
**  Created by wplaat (www.plaatsoft.nl)
**
**  Copyright (C) 2009-2010
**  =======================
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
*/

#include <stdio.h>

#include "General.h" 
#include "MonsterSpecs.h" 
#include "Trace.h" 
#include "Settings.h"

// ------------------------------
// Extern variables
// ------------------------------

extern Game 		game; 
extern Trace    	*trace;
extern Settings	 *settings;

// Monster1 Image
extern const unsigned char     pic101data[];
extern int      pic101length;

// Monster2 Image
extern const unsigned char     pic102data[];
extern int      pic102length;

// Monster3 Image
extern const unsigned char     pic103data[];
extern int      pic103length;

// Monster4 Image
extern const unsigned char     pic104data[];
extern int      pic104length;

// Monster5 Image
extern const unsigned char     pic105data[];
extern int      pic105length;

// Monster6 Image
extern const unsigned char     pic106data[];
extern int      pic106length;

// Monster7 Image
extern const unsigned char     pic107data[];
extern int      pic107length;

// Monster8 Image
extern const unsigned char     pic108data[];
extern int      pic108length;

// Monster9 Image
extern const unsigned char     pic109data[];
extern int      pic109length;

// Monster10 Image
extern const unsigned char     pic110data[];
extern int      pic110length;

// Monster11 Image
extern const unsigned char     pic111data[];
extern int      pic111length;

// Monster12 Image
extern const unsigned char     pic112data[];
extern int      pic112length;

// Monster13 Image
extern const unsigned char     pic113data[];
extern int      pic113length;

// Monster14 Image
extern const unsigned char     pic114data[];
extern int      pic114length;

// Monster15 Image
extern const unsigned char     pic115data[];
extern int      pic115length;

// Monster16 Image
extern const unsigned char     pic116data[];
extern int      pic116length;

// Monster17 Image
extern const unsigned char     pic117data[];
extern int      pic117length;

// Monster18 Image
extern const unsigned char     pic118data[];
extern int      pic118length;

// Monster19 Image
extern const unsigned char     pic119data[];
extern int      pic119length;

// Monster20 Image
extern const unsigned char     pic120data[];
extern int      pic120length;

// Monster21 Image
extern const unsigned char     pic121data[];
extern int      pic121length;

// Monster22 Image
extern const unsigned char     pic122data[];
extern int      pic122length;

// Monster23 Image
extern const unsigned char     pic123data[];
extern int      pic123length;

// Monster24 Image
extern const unsigned char     pic124data[];
extern int      pic124length;

// Monster25 Image
extern const unsigned char     pic125data[];
extern int      pic125length;

// Monster1a Image
extern const unsigned char     pic151data[];
extern int      pic151length;

// Monster2a Image
extern const unsigned char     pic152data[];
extern int      pic152length;

// Monster3a Image
extern const unsigned char     pic153data[];
extern int      pic153length;

// Monster4a Image
extern const unsigned char     pic154data[];
extern int      pic154length;

// Monster5a Image
extern const unsigned char     pic155data[];
extern int      pic155length;

// Monster6a Image
extern const unsigned char     pic156data[];
extern int      pic156length;

// Monster7a Image
extern const unsigned char     pic157data[];
extern int      pic157length;

// Monster8a Image
extern const unsigned char     pic158data[];
extern int      pic158length;

// Monster9a Image
extern const unsigned char     pic159data[];
extern int      pic159length;

// Monster10a Image
extern const unsigned char     pic160data[];
extern int      pic160length;

// Monster11a Image
extern const unsigned char     pic161data[];
extern int      pic161length;

// Monster12a Image
extern const unsigned char     pic162data[];
extern int      pic162length;

// Monster13a Image
extern const unsigned char     pic163data[];
extern int      pic163length;

// Monster14a Image
extern const unsigned char     pic164data[];
extern int      pic164length;

// Monster15a Image
extern const unsigned char     pic165data[];
extern int      pic165length;

// ------------------------------
// Constructor 
// ------------------------------

// Load all monster images
MonsterSpecs::MonsterSpecs()
{
   const char *s_fn="MonsterSpecs::MonsterSpecs";
   trace->event(s_fn,0,"enter");
   
	// Load classic enemies	
	monster1=GRRLIB_LoadTexture( pic101data );
	GRRLIB_InitTileSet(monster1, 32, 32, 0);
	
	monster2=GRRLIB_LoadTexture( pic102data );
	GRRLIB_InitTileSet(monster2, 32, 32, 0);
	
	monster3=GRRLIB_LoadTexture( pic103data );
	GRRLIB_InitTileSet(monster3, 32, 32, 0);
	
	monster4=GRRLIB_LoadTexture( pic104data );
	GRRLIB_InitTileSet(monster4, 32, 32, 0);
	
	monster5=GRRLIB_LoadTexture( pic105data );
	GRRLIB_InitTileSet(monster5, 32, 32, 0);
	
	monster6=GRRLIB_LoadTexture( pic106data );
	GRRLIB_InitTileSet(monster6, 32, 32, 0);
	
	monster7=GRRLIB_LoadTexture( pic107data );
	GRRLIB_InitTileSet(monster7, 32, 32, 0);
	
	monster8=GRRLIB_LoadTexture( pic108data );
	GRRLIB_InitTileSet(monster8, 32, 32, 0);
	
	monster9=GRRLIB_LoadTexture( pic109data );
	GRRLIB_InitTileSet(monster9, 32, 32, 0);
	
	monster10=GRRLIB_LoadTexture( pic110data );
	GRRLIB_InitTileSet(monster10, 32, 32, 0);
	
	monster11=GRRLIB_LoadTexture( pic111data );
	GRRLIB_InitTileSet(monster11, 32, 32, 0);
	
	monster12=GRRLIB_LoadTexture( pic112data );   
	GRRLIB_InitTileSet(monster12, 32, 32, 0);
	
	monster13=GRRLIB_LoadTexture( pic113data );
	GRRLIB_InitTileSet(monster13, 32, 32, 0);
	
	monster14=GRRLIB_LoadTexture( pic114data );
	GRRLIB_InitTileSet(monster14, 32, 32, 0);
	
	monster15=GRRLIB_LoadTexture( pic115data );
	GRRLIB_InitTileSet(monster15, 32, 32, 0);
	
	monster16=GRRLIB_LoadTexture( pic116data );
	GRRLIB_InitTileSet(monster16, 32, 32, 0);
	
	monster17=GRRLIB_LoadTexture( pic117data );
	GRRLIB_InitTileSet(monster17, 32, 32, 0);
	
	monster18=GRRLIB_LoadTexture( pic118data );
	GRRLIB_InitTileSet(monster18, 32, 32, 0);
	
	monster19=GRRLIB_LoadTexture( pic119data );
	GRRLIB_InitTileSet(monster19, 32, 32, 0);
	
	monster20=GRRLIB_LoadTexture( pic120data );
	GRRLIB_InitTileSet(monster20, 32, 32, 0);
	
	monster21=GRRLIB_LoadTexture( pic121data );
	GRRLIB_InitTileSet(monster21, 32, 32, 0);
	
	monster22=GRRLIB_LoadTexture( pic122data );
	GRRLIB_InitTileSet(monster22, 32, 32, 0);
	
	monster23=GRRLIB_LoadTexture( pic123data );
	GRRLIB_InitTileSet(monster23, 32, 32, 0);
	
	monster24=GRRLIB_LoadTexture( pic124data );
	GRRLIB_InitTileSet(monster24, 32, 32, 0);
	
	monster25=GRRLIB_LoadTexture( pic125data );		
	GRRLIB_InitTileSet(monster25, 32, 32, 0);
	
	
	// Load animated enemies
	monster1a=GRRLIB_LoadTexture( pic151data );	
	GRRLIB_InitTileSet(monster1a, 32, 32, 0);
	
	monster2a=GRRLIB_LoadTexture( pic152data );	
	GRRLIB_InitTileSet(monster2a, 32, 32, 0);
	
	monster3a=GRRLIB_LoadTexture( pic153data );	
	GRRLIB_InitTileSet(monster3a, 32, 32, 0);
	
	monster4a=GRRLIB_LoadTexture( pic154data );	
	GRRLIB_InitTileSet(monster4a, 32, 32, 0);
	
	monster5a=GRRLIB_LoadTexture( pic155data );	
	GRRLIB_InitTileSet(monster5a, 32, 32, 0);
	
	monster6a=GRRLIB_LoadTexture( pic156data );	
	GRRLIB_InitTileSet(monster6a, 32, 32, 0);
	
	monster7a=GRRLIB_LoadTexture( pic157data );	
	GRRLIB_InitTileSet(monster7a, 32, 32, 0);
	
	monster8a=GRRLIB_LoadTexture( pic158data );	
	GRRLIB_InitTileSet(monster8a, 32, 32, 0);
	
	monster9a=GRRLIB_LoadTexture( pic159data );	
	GRRLIB_InitTileSet(monster9a, 32, 32, 0);
	
	monster10a=GRRLIB_LoadTexture( pic160data );	
	GRRLIB_InitTileSet(monster10a, 32, 32, 0);
	
	monster11a=GRRLIB_LoadTexture( pic161data );	
	GRRLIB_InitTileSet(monster11a, 32, 32, 0);
	
	monster12a=GRRLIB_LoadTexture( pic162data );	
	GRRLIB_InitTileSet(monster12a, 32, 32, 0);
	
	monster13a=GRRLIB_LoadTexture( pic163data );	
	GRRLIB_InitTileSet(monster13a, 32, 32, 0);
	
	monster14a=GRRLIB_LoadTexture( pic164data );	
	GRRLIB_InitTileSet(monster14a, 32, 32, 0);
	
	monster15a=GRRLIB_LoadTexture( pic165data );	
	GRRLIB_InitTileSet(monster15a, 32, 32, 0);
	
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Destructor
// ------------------------------


// Release all monster images
MonsterSpecs::~MonsterSpecs()
{
   const char *s_fn="MonsterSpecs::~MonsterSpecs";
   trace->event(s_fn,0,"enter");

   trace->event(s_fn,0,"MonsterSpecs destroyed");
	
	// Free classic enemies
   GRRLIB_FreeTexture(monster1);
   GRRLIB_FreeTexture(monster2);
   GRRLIB_FreeTexture(monster3);
   GRRLIB_FreeTexture(monster4);
   GRRLIB_FreeTexture(monster5);
   GRRLIB_FreeTexture(monster6);
   GRRLIB_FreeTexture(monster7);
   GRRLIB_FreeTexture(monster8);
   GRRLIB_FreeTexture(monster9);
   GRRLIB_FreeTexture(monster10);
   GRRLIB_FreeTexture(monster11);
   GRRLIB_FreeTexture(monster12);
   GRRLIB_FreeTexture(monster13);
   GRRLIB_FreeTexture(monster14);
   GRRLIB_FreeTexture(monster15);
   GRRLIB_FreeTexture(monster16);
   GRRLIB_FreeTexture(monster17);
   GRRLIB_FreeTexture(monster18);
   GRRLIB_FreeTexture(monster19);
   GRRLIB_FreeTexture(monster20);
   GRRLIB_FreeTexture(monster21);
   GRRLIB_FreeTexture(monster22);
   GRRLIB_FreeTexture(monster23);
   GRRLIB_FreeTexture(monster24);
   GRRLIB_FreeTexture(monster25);
	
	// Free animated enemies
	GRRLIB_FreeTexture(monster1a);
	GRRLIB_FreeTexture(monster2a);
	GRRLIB_FreeTexture(monster3a);
	GRRLIB_FreeTexture(monster4a);
	GRRLIB_FreeTexture(monster5a);
	GRRLIB_FreeTexture(monster6a);
	GRRLIB_FreeTexture(monster7a);
	GRRLIB_FreeTexture(monster8a);
	GRRLIB_FreeTexture(monster9a);
	GRRLIB_FreeTexture(monster10a);
	GRRLIB_FreeTexture(monster11a);
	GRRLIB_FreeTexture(monster12a);
	GRRLIB_FreeTexture(monster13a);
	GRRLIB_FreeTexture(monster14a);
	GRRLIB_FreeTexture(monster15a);
	  
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Getters
// ------------------------------

// Return Monster Image per Type		
GRRLIB_texImg * MonsterSpecs::getImage(int type)
{
	if (settings->getClassicSprites())
	{
		switch (type)
		{
			case  0: return monster1;		
			case  1: return monster2;
			case  2: return monster3;
			case  3: return monster4;
			case  4: return monster5;
			case  5: return monster6;
			case  6: return monster7;
			case  7: return monster8;
			case  8: return monster9;
			case  9: return monster10;
			case 10: return monster11;
			case 11: return monster12;
			case 12: return monster13;
			case 13: return monster14;
			case 14: return monster15;
			case 15: return monster16;
			case 16: return monster17;
			case 17: return monster18;
			case 18: return monster19;
			case 19: return monster20;
			case 20: return monster21;
			case 21: return monster22;
			case 22: return monster23;
			case 23: return monster24;
			default: return monster25;		
		}
	}
	else
	{
		switch (type)
		{
			case  0: return monster1a;		
			case  1: return monster2a;
			case  2: return monster3a;
			case  3: return monster4a;
			case  4: return monster5a;
			case  5: return monster6a;
			case  6: return monster7a;
			case  7: return monster8a;
			case  8: return monster9a;
			case  9: return monster10a;
			case 10: return monster11a;
			case 11: return monster12a;
			case 12: return monster13a;
			case 13: return monster14a;
			case 14: return monster15a;
			case 15: return monster16;
			case 16: return monster17;
			case 17: return monster18;
			case 18: return monster19;
			case 19: return monster20;
			case 20: return monster21;
			case 21: return monster22;
			case 22: return monster23;
			case 23: return monster24;
			default: return monster25;		
		}
	}
}

// Return energy level per monster type		
int MonsterSpecs::getEnergy(int type)
{
	switch (type)
	{
		case  0: return 5;	
		case  1: return 10;
		case  2: return 15;
		case  3: return 20;
		case  4: return 25;
		case  5: return 30;
		case  6: return 35;
		case  7: return 40;
		case  8: return 45;
		case  9: return 50;
		case 10: return 60;
		case 11: return 80;
		case 12: return 100;
		case 13: return 110;
		case 14: return 120;
		case 15: return 130;
		case 16: return 140;
		case 17: return 160;
		case 18: return 180;
		case 19: return 200;
		case 20: return 220;
		case 21: return 240;
		case 22: return 260;
		case 23: return 300;
		default: return 400;		
	}
}
