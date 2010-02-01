/** 
 *  @file 
 *  @brief The file contains the WeaponSpecs class
 * 
 *  Created by wplaat (www.plaatsoft.nl)
 *
 *  Copyright (C) 2009-2010
 *  =======================
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>

#include "General.h" 
#include "WeaponSpecs.h" 
#include "Weapon.h" 
#include "Trace.h" 

// ------------------------------
// defines
// ------------------------------

#define UPGRADE_STEPS			5
	
#define GUN_PRICE 				100
#define RIFLE_PRICE 				250
#define CANNON_PRICE 			500
#define MISSILE_PRICE 			1000
#define LASER_PRICE 				3000
#define NUKE_PRICE 				6000 

#define GUN_UPGRADE_PRICE  	10
#define RIFLE_UPGRADE_PRICE 	25
#define CANNON_UPGRADE_PRICE 	50
#define MISSILE_UPGRADE_PRICE 100
#define LASER_UPGRADE_PRICE 	300
#define NUKE_UPGRADE_PRICE  	600

#define GUN_MIN_POWER 			2
#define RIFLE_MIN_POWER 		10
#define CANNON_MIN_POWER 		20
#define MISSILE_MIN_POWER		40
#define LASER_MIN_POWER 		25
#define NUKE_MIN_POWER 			200

#define GUN_STEP_POWER  		1
#define RIFLE_STEP_POWER  		2
#define CANNON_STEP_POWER  	3
#define MISSILE_STEP_POWER 	5
#define LASER_STEP_POWER 		5
#define NUKE_STEP_POWER 		10	

#define GUN_MIN_RANGE 			40
#define RIFLE_MIN_RANGE 		45
#define CANNON_MIN_RANGE 		50
#define MISSILE_MIN_RANGE 		70
#define LASER_MIN_RANGE 		60
#define NUKE_MIN_RANGE 			50

#define GUN_STEP_RANGE  		5
#define RIFLE_STEP_RANGE  		5
#define CANNON_STEP_RANGE  	5
#define MISSILE_STEP_RANGE 	7
#define LASER_STEP_RANGE 		7
#define NUKE_STEP_RANGE 		5

#define GUN_MIN_RATE 			12
#define RIFLE_MIN_RATE  		11
#define CANNON_MIN_RATE  		10
#define MISSILE_MIN_RATE  		8
#define LASER_MIN_RATE  		7
#define NUKE_MIN_RATE  			9

#define GUN_STEP_RATE   		1
#define RIFLE_STEP_RATE   		1
#define CANNON_STEP_RATE   	1
#define MISSILE_STEP_RATE  	1
#define LASER_STEP_RATE  		1
#define NUKE_STEP_RATE  		1

#define GUN_FIRE_MODE   		FIRE_MODE_NEAREST_TO_BASE
#define RIFLE_FIRE_MODE			FIRE_MODE_NEAREST_TO_BASE
#define CANNON_FIRE_MODE		FIRE_MODE_HIGHEST_ENERGY
#define MISSILE_FIRE_MODE		FIRE_MODE_HIGHEST_ENERGY
#define LASER_FIRE_MODE			FIRE_MODE_FASTEST
#define NUKE_FIRE_MODE			FIRE_MODE_FASTEST

#define GUN_FIRE_MODE_NAME  	  "Nearest to base" 		
#define RIFLE_FIRE_MODE_NAME	  "Nearest to base"
#define CANNON_FIRE_MODE_NAME	  "Highest energy"
#define MISSILE_FIRE_MODE_NAME  "Highest energy"
#define LASER_FIRE_MODE_NAME    "Fastest Enemy"
#define NUKE_FIRE_MODE_NAME     "Fastest Enemy"

// ------------------------------
// Extern variables
// ------------------------------

extern Game	game; 
extern Trace *trace;

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

// Weapon1a Image
extern const unsigned char     pic506data[];
extern int      pic506length;

// Weapon2a Image
extern const unsigned char     pic507data[];
extern int      pic507length;

// Weapon3a Image
extern const unsigned char     pic508data[];
extern int      pic508length;

// Weapon4a Image
extern const unsigned char     pic509data[];
extern int      pic509length;

// Weapon5a Image
extern const unsigned char     pic510data[];
extern int      pic510length;

// Weapon6a Image
extern const unsigned char     pic511data[];
extern int      pic511length;

// ------------------------------
// Constructor 
// ------------------------------

/**
 * Constructor
 * Init all properties with default values.
 */
WeaponSpecs::WeaponSpecs()
{
   const char *s_fn="WeaponSpecs::WeaponSpecs";
   trace->event(s_fn,0,"enter");
   
	weapon1=GRRLIB_LoadTexture( pic500data );
	GRRLIB_InitTileSet(weapon1, 32, 32, 0);

	weapon2=GRRLIB_LoadTexture( pic501data );
	GRRLIB_InitTileSet(weapon2, 32, 32, 0);

	weapon3=GRRLIB_LoadTexture( pic502data );
	GRRLIB_InitTileSet(weapon3, 32, 32, 0);
	
	weapon4=GRRLIB_LoadTexture( pic503data );
	GRRLIB_InitTileSet(weapon4, 32, 32, 0);
	
	weapon5=GRRLIB_LoadTexture( pic504data );
	GRRLIB_InitTileSet(weapon5, 32, 32, 0);
	
	weapon6=GRRLIB_LoadTexture( pic505data );
	GRRLIB_InitTileSet(weapon6, 32, 32, 0);
	
	weapon1a=GRRLIB_LoadTexture( pic506data );
	GRRLIB_InitTileSet(weapon1a, 32, 32, 0);
	
	weapon2a=GRRLIB_LoadTexture( pic507data );
	GRRLIB_InitTileSet(weapon2a, 32, 32, 0);
	
	weapon3a=GRRLIB_LoadTexture( pic508data );
	GRRLIB_InitTileSet(weapon3a, 32, 32, 0);
	
	weapon4a=GRRLIB_LoadTexture( pic509data );
	GRRLIB_InitTileSet(weapon4a, 32, 32, 0);
	
	weapon5a=GRRLIB_LoadTexture( pic510data );
	GRRLIB_InitTileSet(weapon5a, 32, 32, 0);
	
	weapon6a=GRRLIB_LoadTexture( pic511data );
	GRRLIB_InitTileSet(weapon6a, 32, 32, 0);
	
	resetCounter();
		
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Destructor
// ------------------------------

/**
 * Destructor
 * Clean up all allocated memory
 */
WeaponSpecs::~WeaponSpecs()
{
   const char *s_fn="WeaponSpecs::~WeaponSpecs";
   trace->event(s_fn,0,"enter");

   trace->event(s_fn,0,"WeaponSpecs destroyed");
	
	// Free memory
   GRRLIB_FreeTexture(weapon1);
   GRRLIB_FreeTexture(weapon2);
   GRRLIB_FreeTexture(weapon3);
   GRRLIB_FreeTexture(weapon4);
   GRRLIB_FreeTexture(weapon5);
   GRRLIB_FreeTexture(weapon6);
	
	GRRLIB_FreeTexture(weapon1a);
   GRRLIB_FreeTexture(weapon2a);
   GRRLIB_FreeTexture(weapon3a);
   GRRLIB_FreeTexture(weapon4a);
   GRRLIB_FreeTexture(weapon5a);
   GRRLIB_FreeTexture(weapon6a);
	  
   trace->event(s_fn,0,"leave");
}

// ------------------------------
// Others
// ------------------------------

/**
 * reset weapon counters
 */
void WeaponSpecs::resetCounter(void)
{
   const char *s_fn="WeaponSpecs::resetCounter";
   trace->event(s_fn,0,"enter");
	
	gunCounter=0;
	rifleCounter=0;
	cannonCounter=0;
	missileCounter=0;
	laserCounter=0;
	nukeCounter=0;
	
	trace->event(s_fn,0,"leave");
}

// ------------------------------
// Getters
// ------------------------------

/**
 * Return Weapon Image (with 16x4 frames) per Type		
 */
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
				
		case 2:  // Cannon
				 return weapon3;
				 break;
				
		case 3:  // Missile
				 return weapon4;
				 break;
				
		case 4:  // Laser
				 return weapon5;
				 break;
				
		default: // Nuke
				 return weapon6;
				 break;
	}
}

/**
 * Return Weapon Image (1 frame) per Type		
 */
GRRLIB_texImg * WeaponSpecs::getImageSpecial(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return weapon1a;
				 break;
				
		case 1:  // Rifle
				 return weapon2a;
				 break;
				
		case 2:  // Cannon
				 return weapon3a;
				 break;
				
		case 3:  // Missile
				 return weapon4a;
				 break;
				
		case 4:  // Laser
				 return weapon5a;
				 break;
				
		default: // Nuke
				 return weapon6a;
				 break;
	}
}

/**
 * Get Weapon Name
 *
 * @param type		The weapon type.
 *
 * @return The weapon name
 */
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
				
		case 2:  // Cannon
				 return "Cannon";
				 break;
				
		case 3:  // Missile
				 return "Missile";
				 break;
				
		case 4:  // Laser
				 return "Laser";
				 break;
				
		default: // Nuke
				 return "Nuke";
				 break;
	}
}

/**
 * Get Weapon Price
 *
 * @param type		The weapon type.
 *
 * @return The weapon price
 */
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
				
		case 2:  // Cannon
				 return CANNON_PRICE;
				 break;
				
		case 3:  // Missile
				 return MISSILE_PRICE;
				 break;
				
		case 4:  // Laser
				 return LASER_PRICE;
				 break;
				
		default: // Nuke
				 return NUKE_PRICE;
				 break;
	}
}

/**
 * Get Weapon start upgrade price
 *
 * @param type		The weapon type.
 *
 * @return The weapon start upgrade price
 */
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
				
		case 2:  // Cannon
				 return CANNON_UPGRADE_PRICE;
				 break;
				
		case 3:  // Missile
				 return MISSILE_UPGRADE_PRICE;
				 break;
				
		case 4:  // Laser
				 return LASER_UPGRADE_PRICE;
				 break;
				
		default: // Nuke
				 return NUKE_UPGRADE_PRICE;
				 break;
	}
}

/**
 * Get Weapon minimum power value
 *
 * @param type		The weapon type.
 *
 * @return The minimum power value.
 */
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
				
		case 2:  // Cannon
				 return CANNON_MIN_POWER;
				 break;
				
		case 3:  // Missile
				 return MISSILE_MIN_POWER;
				 break;
				
		case 4:  // Laser
				 return LASER_MIN_POWER;
				 break;
				
		default: // Nuke
				 return NUKE_MIN_POWER;
				 break;
	}
}

/**
 * Get Weapon minimum range value
 *
 * @param type		The weapon type.
 *
 * @return The minimum range value.
 */
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
				
		case 2:  // Cannon
				 return CANNON_MIN_RANGE;
				 break;
				
		case 3:  // Missile
				 return MISSILE_MIN_RANGE;
				 break;
				
		case 4:  // Laser
				 return LASER_MIN_RANGE;
				 break;
				
		default: // Nuke
				 return NUKE_MIN_RANGE;
				 break;
	}
}

/**
 * Get Weapon minimum rate value
 *
 * @param type		The weapon type.
 *
 * @return The minimum rate value.
 */
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
				
		case 2:  // Cannon
				 return CANNON_MIN_RATE;
				 break;
				
		case 3:  // Missile
				 return MISSILE_MIN_RATE;
				 break;
				
		case 4:  // Laser
				 return LASER_MIN_RATE;
				 break;
				
		default: // Nuke
				 return NUKE_MIN_RATE;
				 break;
	}
}

/**
 * Get Weapon maximum power value
 *
 * @param type		The weapon type.
 *
 * @return The maximum power value.
 */
int WeaponSpecs::getMaxPower(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_MIN_POWER+(GUN_STEP_POWER*UPGRADE_STEPS);
				 break;
				
		case 1:  // Rifle
				 return RIFLE_MIN_POWER+(RIFLE_STEP_POWER*UPGRADE_STEPS);
				 break;
				
		case 2:  // Cannon
				 return CANNON_MIN_POWER+(CANNON_STEP_POWER*UPGRADE_STEPS);
				 break;
				
		case 3:  // Missile
				 return MISSILE_MIN_POWER+(MISSILE_STEP_POWER*UPGRADE_STEPS);
				 break;
				
		case 4:  // Laser
				 return LASER_MIN_POWER+(LASER_STEP_POWER*UPGRADE_STEPS);
				 break;
				
		default: // Nuke
				 return NUKE_MIN_POWER+(NUKE_STEP_POWER*UPGRADE_STEPS);
				 break;
	}
}


/**
 * Get Weapon maximum range value
 *
 * @param type		The weapon type.
 *
 * @return The maximum range value.
 */
int WeaponSpecs::getMaxRange(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_MIN_RANGE+(GUN_STEP_RANGE*UPGRADE_STEPS);
				 break;
				
		case 1:  // Rifle
				 return RIFLE_MIN_RANGE+(RIFLE_STEP_RANGE*UPGRADE_STEPS);
				 break;
				
		case 2:  // Cannon
				 return CANNON_MIN_RANGE+(CANNON_STEP_RANGE*UPGRADE_STEPS);
				 break;
				
		case 3:  // Missile
				 return MISSILE_MIN_RANGE+(MISSILE_STEP_RANGE*UPGRADE_STEPS);
				 break;
				
		case 4:  // Laser
				 return LASER_MIN_RANGE+(LASER_STEP_RANGE*UPGRADE_STEPS);
				 break;
				
		default: // Nuke
				 return NUKE_MIN_RANGE+(NUKE_STEP_RANGE*UPGRADE_STEPS);
				 break;
	}
}

/**
 * Get Weapon maximum rate value
 *
 * @param type		The weapon type.
 *
 * @return The maximum rate value.
 */
int WeaponSpecs::getMaxRate(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_MIN_RATE-(GUN_STEP_RATE*UPGRADE_STEPS);
				 break;
				
		case 1:  // Rifle
				 return RIFLE_MIN_RATE-(GUN_STEP_RATE*UPGRADE_STEPS);
				 break;
				
		case 2:  // Cannon
				 return CANNON_MIN_RATE-(GUN_STEP_RATE*UPGRADE_STEPS);
				 break;
				
		case 3:  // Missile
				 return MISSILE_MIN_RATE-(GUN_STEP_RATE*UPGRADE_STEPS);
				 break;
				
		case 4:  // Laser
				 return LASER_MIN_RATE-(GUN_STEP_RATE*UPGRADE_STEPS);
				 break;
				
		default: // Nuke
				 return NUKE_MIN_RATE-(GUN_STEP_RATE*UPGRADE_STEPS);
				 break;
	}
}

/**
 * Get Weapon power step value
 *
 * @param type		The weapon type.
 *
 * @return The power step value.
 */
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
				
		case 2:  // Cannon
				 return CANNON_STEP_POWER;
				 break;
				
		case 3:  // Missile
				 return MISSILE_STEP_POWER;
				 break;
				
		case 4:  // Laser
				 return LASER_STEP_POWER;
				 break;
				
		default: // Nuk
				 return NUKE_STEP_POWER;
				 break;
	}
}

/**
 * Get Weapon range step value
 *
 * @param type		The weapon type.
 *
 * @return The range step value.
 */
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
				
		case 2:  // Cannon
				 return CANNON_STEP_RANGE;
				 break;
				
		case 3:  // Missile
				 return MISSILE_STEP_RANGE;
				 break;
				
		case 4:  // Laser
				 return LASER_STEP_RANGE;
				 break;
				
		default: // Nuke
				 return NUKE_STEP_RANGE;
				 break;
	}
}

/**
 * Get Weapon rate step value
 *
 * @param type		The weapon type.
 *
 * @return The rate step value.
 */
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
				
		case 2:  // Cannon
				 return CANNON_STEP_RATE;
				 break;
				
		case 3:  // Missile
				 return MISSILE_STEP_RATE;
				 break;
				
		case 4:  // Laser
				 return LASER_STEP_RATE;
				 break;
				
		default: // Nuke
				 return NUKE_STEP_RATE;
				 break;
	}
}

/**
 * Get Weapon unique id
 *
 * @param type		The weapon type.
 *
 * @return unique id
 */
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
				
		case 2:  // Cannon
				 return ++cannonCounter;
				 break;
				
		case 3:  // Missile
				 return ++missileCounter;
				 break;
				
		case 4:  // Laser
				 return ++laserCounter;
				 break;
				
		default: // Nuke
				 return ++nukeCounter;
				 break;
	}
}


/**
 * Get Weapon fire mode 
 *
 * @param type		The weapon type.
 *
 * @return fire mode
 */
int WeaponSpecs::getFireMode(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_FIRE_MODE;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_FIRE_MODE;
				 break;
				
		case 2:  // Cannon
				 return CANNON_FIRE_MODE;
				 break;
				
		case 3:  // Missile
				 return MISSILE_FIRE_MODE;
				 break;
				
		case 4:  // Laser
				 return LASER_FIRE_MODE;
				 break;
				
		default: // Nuke
				 return NUKE_FIRE_MODE;
				 break;
	}
}


/**
 * Get Weapon fire mode name 
 *
 * @param type		The weapon type.
 *
 * @return The fire mode name
 */
const char *WeaponSpecs::getFireModeName(int type)
{
	switch (type)
	{
		case 0:  // Gun
				 return GUN_FIRE_MODE_NAME;
				 break;
				
		case 1:  // Rifle
				 return RIFLE_FIRE_MODE_NAME;
				 break;
				
		case 2:  // Cannon
				 return CANNON_FIRE_MODE_NAME;
				 break;
				
		case 3:  // Missile
				 return MISSILE_FIRE_MODE_NAME;
				 break;
				
		case 4:  // Laser
				 return LASER_FIRE_MODE_NAME;
				 break;
				
		default: // Nuke
				 return NUKE_FIRE_MODE_NAME;
				 break;
	}
}