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
*/

#include <stdio.h>

#include "General.h" 
#include "WeaponSpecs.h" 
#include "Trace.h" 

// ------------------------------
// defines
// ------------------------------

#define GUN_PRICE 				100
#define RIFLE_PRICE 				200
#define CANON_PRICE 				500
#define MISSLE_PRICE 			1000
#define LASER_PRICE 				2000
#define NUCK_PRICE 				4000

#define GUN_UPGRADE_PRICE  	10
#define RIFLE_UPGRADE_PRICE 	25
#define CANON_UPGRADE_PRICE 	50
#define LASER_UPGRADE_PRICE 	100
#define MISSLE_UPGRADE_PRICE 	100
#define NUCK_UPGRADE_PRICE  	250

#define GUN_MIN_POWER 			2
#define RIFLE_MIN_POWER 		4
#define CANON_MIN_POWER 		12
#define MISSLE_MIN_POWER		20
#define LASER_MIN_POWER 		30
#define NUCK_MIN_POWER 			100

#define GUN_MAX_POWER   		10
#define RIFLE_MAX_POWER   		14
#define CANON_MAX_POWER   		24
#define MISSLE_MAX_POWER   	34
#define LASER_MAX_POWER   		44
#define NUCK_MAX_POWER   		114

#define GUN_MIN_RANGE 			50
#define RIFLE_MIN_RANGE 		80
#define CANON_MIN_RANGE 		60
#define MISSLE_MIN_RANGE 		80
#define LASER_MIN_RANGE 		80
#define NUCK_MIN_RANGE 			80

#define GUN_MAX_RANGE   		75
#define RIFLE_MAX_RANGE   		100
#define CANON_MAX_RANGE   		80
#define MISSLE_MAX_RANGE   	100
#define LASER_MAX_RANGE   		100
#define NUCK_MAX_RANGE   		100

#define GUN_MIN_RATE 			10
#define RIFLE_MIN_RATE  		8
#define CANON_MIN_RATE  		10
#define MISSLE_MIN_RATE  		8
#define LASER_MIN_RATE  		6
#define NUCK_MIN_RATE  			10

#define GUN_MAX_RATE    		6
#define RIFLE_MAX_RATE   		4
#define CANON_MAX_RATE    		6
#define MISSLE_MAX_RATE    	4
#define LASER_MAX_RATE    		2
#define NUCK_MAX_RATE    		6

#define GUN_STEP_POWER  		2
#define RIFLE_STEP_POWER  		2
#define CANON_STEP_POWER  		2
#define MISSLE_STEP_POWER 		2
#define LASER_STEP_POWER 		2
#define NUCK_STEP_POWER 		2	

#define GUN_STEP_RANGE  		5
#define RIFLE_STEP_RANGE  		5
#define CANON_STEP_RANGE  		5
#define MISSLE_STEP_RANGE 		5
#define LASER_STEP_RANGE 		5
#define NUCK_STEP_RANGE 		5

#define GUN_STEP_RATE   		1
#define RIFLE_STEP_RATE   		1
#define CANON_STEP_RATE   		1
#define MISSLE_STEP_RATE  		1
#define LASER_STEP_RATE  		1
#define NUCK_STEP_RATE  		1

// ------------------------------
// Extern variables
// ------------------------------

extern Game 		game; 
extern Trace    	*trace;

// Weapon1 Image
extern const unsigned char     pic500data[];
extern int      pic500length;

// Weapon2 Image
extern const unsigned char     pic501data[];
extern int      pic501length;

// Weapon3 Image
extern const unsigned char     pic502data[];
extern int      pic502length;

// Weapon4 Image
extern const unsigned char     pic503data[];
extern int      pic503length;

// Weapon5 Image
extern const unsigned char     pic504data[];
extern int      pic504length;

// Weapon6 Image
extern const unsigned char     pic505data[];
extern int      pic505length;

// ------------------------------
// Constructor 
// ------------------------------

WeaponSpecs::WeaponSpecs()
{
   const char *s_fn="WeaponSpecs::WeaponSpecs";
   trace->event(s_fn,0,"enter");
   
	weapon1=GRRLIB_LoadTexture( pic500data );
	weapon2=GRRLIB_LoadTexture( pic501data );
	weapon3=GRRLIB_LoadTexture( pic502data );
	weapon4=GRRLIB_LoadTexture( pic503data );
	weapon5=GRRLIB_LoadTexture( pic504data );
	weapon6=GRRLIB_LoadTexture( pic505data );
      
	resetCounter();
		
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Destructor
// ------------------------------

WeaponSpecs::~WeaponSpecs()
{
   const char *s_fn="WeaponSpecs::~WeaponSpecs";
   trace->event(s_fn,0,"enter");

   trace->event(s_fn,0,"WeaponSpecs destroyed", index);
	
	// Free memory
   GRRLIB_FreeTexture(weapon1);
   GRRLIB_FreeTexture(weapon2);
   GRRLIB_FreeTexture(weapon3);
   GRRLIB_FreeTexture(weapon4);
   GRRLIB_FreeTexture(weapon5);
   GRRLIB_FreeTexture(weapon6);
	  
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Others
// ------------------------------

void WeaponSpecs::resetCounter(void)
{
   const char *s_fn="WeaponSpecs::resetCounter";
   trace->event(s_fn,0,"enter");
	
	gunCounter=0;
	rifleCounter=0;
	canonCounter=0;
	missleCounter=0;
	laserCounter=0;
	nuckCounter=0;
	
	trace->event(s_fn,0,"leave");
}

// ------------------------------
// Getters
// ------------------------------

// Return Weapon Image per Type		
GRRLIB_texImg * WeaponSpecs::getImage(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return weapon1;
				 break;
				
		case 1:  // Rifle
				 return weapon2;
				 break;
				
		case 2:  // Canon
				 return weapon3;
				 break;
				
		case 3:  // Missle
				 return weapon4;
				 break;
				
		case 4:  // Laser
				 return weapon5;
				 break;
				
		default: // Nuck
				 return weapon6;
				 break;
	}
}

// Return Weapon Name
const char *WeaponSpecs::getName(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return "Gun";
				 break;
				
		case 1:  // Rifle
				 return "Rifle";
				 break;
				
		case 2:  // Canon
				 return "Canon";
				 break;
				
		case 3:  // Missle
				 return "Missle";
				 break;
				
		case 4:  // Laser
				 return "Laser";
				 break;
				
		default: // Nuck
				 return "Nuck";
				 break;
	}
}


// Return Weapon price per type
int WeaponSpecs::getPrice(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_PRICE;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_PRICE;
				 break;
				
		case 2:  // Canon
				 return CANON_PRICE;
				 break;
				
		case 3:  // Missle
				 return MISSLE_PRICE;
				 break;
				
		case 4:  // Laser
				 return LASER_PRICE;
				 break;
				
		default: // Nuck
				 return NUCK_PRICE;
				 break;
	}
}


int WeaponSpecs::getUpgradePrice(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_UPGRADE_PRICE;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_UPGRADE_PRICE;
				 break;
				
		case 2:  // Canon
				 return CANON_UPGRADE_PRICE;
				 break;
				
		case 3:  // Missle
				 return MISSLE_UPGRADE_PRICE;
				 break;
				
		case 4:  // Laser
				 return LASER_UPGRADE_PRICE;
				 break;
				
		default: // Nuck
				 return NUCK_UPGRADE_PRICE;
				 break;
	}
}

// Return min Power per type
int WeaponSpecs::getMinPower(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_MIN_POWER;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_MIN_POWER;
				 break;
				
		case 2:  // Canon
				 return CANON_MIN_POWER;
				 break;
				
		case 3:  // Missle
				 return MISSLE_MIN_POWER;
				 break;
				
		case 4:  // Laser
				 return LASER_MIN_POWER;
				 break;
				
		default: // Nuck
				 return NUCK_MIN_POWER;
				 break;
	}
}

// Return min Power per type
int WeaponSpecs::getMinRange(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_MIN_RANGE;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_MIN_RANGE;
				 break;
				
		case 2:  // Canon
				 return CANON_MIN_RANGE;
				 break;
				
		case 3:  // Missle
				 return MISSLE_MIN_RANGE;
				 break;
				
		case 4:  // Laser
				 return LASER_MIN_RANGE;
				 break;
				
		default: // Nuck
				 return NUCK_MIN_RANGE;
				 break;
	}
}

// Return min rate per type
int WeaponSpecs::getMinRate(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_MIN_RATE;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_MIN_RATE;
				 break;
				
		case 2:  // Canon
				 return CANON_MIN_RATE;
				 break;
				
		case 3:  // Missle
				 return MISSLE_MIN_RATE;
				 break;
				
		case 4:  // Laser
				 return LASER_MIN_RATE;
				 break;
				
		default: // Nuck
				 return NUCK_MIN_RATE;
				 break;
	}
}

// Return Max Power per type
int WeaponSpecs::getMaxPower(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_MAX_POWER;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_MAX_POWER;
				 break;
				
		case 2:  // Canon
				 return CANON_MAX_POWER;
				 break;
				
		case 3:  // Missle
				 return MISSLE_MAX_POWER;
				 break;
				
		case 4:  // Laser
				 return LASER_MAX_POWER;
				 break;
				
		default: // Nuck
				 return NUCK_MAX_POWER;
				 break;
	}
}


// Return Max Power per type
int WeaponSpecs::getMaxRange(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_MAX_RANGE;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_MAX_RANGE;
				 break;
				
		case 2:  // Canon
				 return CANON_MAX_RANGE;
				 break;
				
		case 3:  // Missle
				 return MISSLE_MAX_RANGE;
				 break;
				
		case 4:  // Laser
				 return LASER_MAX_RANGE;
				 break;
				
		default: // Nuck
				 return NUCK_MAX_RANGE;
				 break;
	}
}

// Return Max rate per type
int WeaponSpecs::getMaxRate(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_MAX_RATE;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_MAX_RATE;
				 break;
				
		case 2:  // Canon
				 return CANON_MAX_RATE;
				 break;
				
		case 3:  // Missle
				 return MISSLE_MAX_RATE;
				 break;
				
		case 4:  // Laser
				 return LASER_MAX_RATE;
				 break;
				
		default: // Nuck
				 return NUCK_MAX_RATE;
				 break;
	}
}

int WeaponSpecs::getStepPower(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_STEP_POWER;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_STEP_POWER;
				 break;
				
		case 2:  // Canon
				 return CANON_STEP_POWER;
				 break;
				
		case 3:  // Missle
				 return MISSLE_STEP_POWER;
				 break;
				
		case 4:  // Laser
				 return LASER_STEP_POWER;
				 break;
				
		default: // Nuck
				 return NUCK_STEP_POWER;
				 break;
	}
}

int WeaponSpecs::getStepRange(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_STEP_RANGE;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_STEP_RANGE;
				 break;
				
		case 2:  // Canon
				 return CANON_STEP_RANGE;
				 break;
				
		case 3:  // Missle
				 return MISSLE_STEP_RANGE;
				 break;
				
		case 4:  // Laser
				 return LASER_STEP_RANGE;
				 break;
				
		default: // Nuck
				 return NUCK_STEP_RANGE;
				 break;
	}
}

int WeaponSpecs::getStepRate(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_STEP_RATE;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_STEP_RATE;
				 break;
				
		case 2:  // Canon
				 return CANON_STEP_RATE;
				 break;
				
		case 3:  // Missle
				 return MISSLE_STEP_RATE;
				 break;
				
		case 4:  // Laser
				 return LASER_STEP_RATE;
				 break;
				
		default: // Nuck
				 return NUCK_STEP_RATE;
				 break;
	}
}


int WeaponSpecs::getCounter(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return ++gunCounter;
				 break;
				
		case 1:  // Rifle
				 return ++rifleCounter;
				 break;
				
		case 2:  // Canon
				 return ++canonCounter;
				 break;
				
		case 3:  // Missle
				 return ++missleCounter;
				 break;
				
		case 4:  // Laser
				 return ++laserCounter;
				 break;
				
		default: // Nuck
				 return ++nuckCounter;
				 break;
	}
}