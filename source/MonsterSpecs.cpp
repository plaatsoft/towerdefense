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

// ------------------------------
// Extern variables
// ------------------------------

extern Game 		game; 
extern Trace    	*trace;

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


// ------------------------------
// Constructor 
// ------------------------------

// Load all monster images
MonsterSpecs::MonsterSpecs()
{
   const char *s_fn="MonsterSpecs::MonsterSpecs";
   trace->event(s_fn,0,"enter");
   
	monster1=GRRLIB_LoadTexture( pic101data );
	monster2=GRRLIB_LoadTexture( pic102data );
	monster3=GRRLIB_LoadTexture( pic103data );
	monster4=GRRLIB_LoadTexture( pic104data );
	monster5=GRRLIB_LoadTexture( pic105data );
	monster6=GRRLIB_LoadTexture( pic106data );
	monster7=GRRLIB_LoadTexture( pic107data );
	monster8=GRRLIB_LoadTexture( pic108data );
	monster9=GRRLIB_LoadTexture( pic109data );
	monster10=GRRLIB_LoadTexture( pic110data );
	monster11=GRRLIB_LoadTexture( pic111data );
	monster12=GRRLIB_LoadTexture( pic112data );   
	monster13=GRRLIB_LoadTexture( pic113data );
	monster14=GRRLIB_LoadTexture( pic114data );
	monster15=GRRLIB_LoadTexture( pic115data );
	monster16=GRRLIB_LoadTexture( pic116data );
	monster17=GRRLIB_LoadTexture( pic117data );
	monster18=GRRLIB_LoadTexture( pic118data );
	monster19=GRRLIB_LoadTexture( pic119data );
	monster20=GRRLIB_LoadTexture( pic120data );
	monster21=GRRLIB_LoadTexture( pic121data );
	monster22=GRRLIB_LoadTexture( pic122data );
	monster23=GRRLIB_LoadTexture( pic123data );
	monster24=GRRLIB_LoadTexture( pic124data );
	monster25=GRRLIB_LoadTexture( pic125data );		
	
	monster1a=GRRLIB_LoadTexture( pic151data );	
	GRRLIB_InitTileSet(monster1a, 32, 32, 0);
      
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
	
	// Free memory
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
	
	GRRLIB_FreeTexture(monster1a);
	  
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Getters
// ------------------------------

// Return Monster Image per Type		
GRRLIB_texImg * MonsterSpecs::getImage(int type)
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
