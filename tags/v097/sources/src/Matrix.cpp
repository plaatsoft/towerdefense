/** 
 *  @file 
 *  @brief The file contain the Matrix class methodes
 *  @author wplaat
 *
 *  Copyright (C) 2008-2010 PlaatSoft
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

/*
 * This class contain all nessary game matrix parameters.
 * Which this parameters the game play can be easy adapted.
 */
 
#include <stdio.h>
#include <gccore.h>
#include <ogcsys.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ogcsys.h>
#include <stdarg.h>
#include <time.h>

#include "General.h"
#include "Matrix.h"
#include "Trace.h"

#define MAX_DELAY_BETWEEN_WAVES    		(120 * AVERAGE_FPS)   // 120 seconds
#define MIN_DELAY_BETWEEN_WAVES      	(5 * AVERAGE_FPS)     // 5 seconds

#define MAX_DELAY_BETWEEN_ENEMIES  		(4 * AVERAGE_FPS)     // 4 seconds  
#define MIN_DELAY_BETWEEN_ENEMIES    	5             		  	 // 0.2 seconds

#define START_CASH_EASY    				1000
#define START_CASH_MEDIUM  				3000
#define START_CASH_HARD    				5000

#define MIN_AMOUNT_OF_ENEMIES_IN_WAVE  4
#define MAX_AMOUNT_OF_ENEMIES_IN_WAVE  90

extern 	Trace *trace;
 
// ------------------------------
// Constructor
// ------------------------------

/**
 * Constructor
 * Init all properties with default values.
 */
Matrix::Matrix()
{
	const char *s_fn="Matrix::Matrix";
   trace->event(s_fn,0,"enter");
	
	wave=0;
	level=0;
	waveDelay = MAX_DELAY_BETWEEN_WAVES; 
	enemyDelay = MAX_DELAY_BETWEEN_ENEMIES;
	stepFactor = 1;
	minStep = 1;
	enemiesInWave=MIN_AMOUNT_OF_ENEMIES_IN_WAVE;
	
	trace->event(s_fn,0,"leave");
}

// ------------------------------
// Destructor
// -------------------------------

/**
 * Destructor
 * Clean up all allocated memory
 */
Matrix::~Matrix()
{
	const char *s_fn="Matrix::~Matrix";
   trace->event(s_fn,0,"enter");
	
	trace->event(s_fn,0,"leave");
}

// ------------------------------
// Methode
// ------------------------------

/**
 * Calculate game matrix parameters.
 */
void Matrix::calculateMatrix(void)
{
	const char *s_fn="Matrix::calculateMatrix";
   trace->event(s_fn,0,"enter");
	
   // Determine new stepFactor
	if ((wave>=0) && (wave<10)) 
	{
		stepFactor = 1;
		minStep = 1;
		bonusDelay= 0;
	}
	if ((wave>=10) && (wave<20)) 
	{
		stepFactor = 2;
		minStep = 1;
	}
	
	if ((wave>=20) && (wave<35)) 
	{
		stepFactor = 3;
		minStep = 1;
	}
	
	if ((wave>=35) && (wave<50)) 
	{
		stepFactor = 2;
		minStep = 2;
		bonusDelay = AVERAGE_FPS;
	}
	
	if ((wave>=50) && (wave<60)) 
	{
		stepFactor = 3;
		minStep = 2;
		bonusDelay = AVERAGE_FPS;
	}
	
	if ((wave>=60) && (wave<70)) 
	{
		stepFactor = 2;
		minStep = 3;
		bonusDelay = AVERAGE_FPS*2;
	}
	
	if ((wave>=70) && (wave<80)) 
	{
		stepFactor = 3;
		minStep = 3;
		bonusDelay = AVERAGE_FPS*2;
	}
	
	if ((wave>=80) && (wave<90)) 
	{
		stepFactor = 4;
		minStep = 3;
		bonusDelay = AVERAGE_FPS*2;
	}
	
	if ((wave>=90) && (wave<110)) 
	{
		stepFactor = 3;
		minStep = 4;
		bonusDelay = AVERAGE_FPS*3;
	}
	
	if ((wave>=110) && (wave<130)) 
	{
		stepFactor = 4;
		minStep = 4;
		bonusDelay = AVERAGE_FPS*2;
	}
	
	if ((wave>=130) && (wave<150)) 
	{
		stepFactor = 5;
		minStep = 4;
		bonusDelay = AVERAGE_FPS*1;
	}
	
	if (wave>=150) 
	{
		stepFactor = 4;
		minStep = 5;
		bonusDelay = 0;
	}

	// Calculate how much enemies will be in the wave
	enemiesInWave=MIN_AMOUNT_OF_ENEMIES_IN_WAVE+wave;
	if (enemiesInWave>MAX_AMOUNT_OF_ENEMIES_IN_WAVE) 
	{
		enemiesInWave=MAX_AMOUNT_OF_ENEMIES_IN_WAVE;
	}

	// Calculate delay between two enemies
	enemyDelay=MAX_DELAY_BETWEEN_ENEMIES-(wave*3)+bonusDelay;
	if (enemyDelay<MIN_DELAY_BETWEEN_ENEMIES) 
	{
		enemyDelay=MIN_DELAY_BETWEEN_ENEMIES;
	}
	
	// Calculate delay between two waves
	waveDelay=MAX_DELAY_BETWEEN_WAVES-(2 * AVERAGE_FPS * wave); 
	if (waveDelay<MIN_DELAY_BETWEEN_WAVES) 
	{
		waveDelay=MIN_DELAY_BETWEEN_WAVES;
	}
	
	trace->event(s_fn,0,"leave");
}

// ------------------------------
// Getters
// ------------------------------

/**
 * Get how much enemies will be in a wave
 * @return amount of enemies
 */
int Matrix::getEnemyAmount( void )
{	
	const char *s_fn="Matrix::getEnemyAmount";
   trace->event(s_fn,0,"enter");
	
	trace->event(s_fn,0,"leave [enemiesInWave=%d]",enemiesInWave);
	return enemiesInWave;
}

/**
 * Get enemy step size
 * @return enemy step size
 */
int Matrix::getEnemyStep( void )
{	
	const char *s_fn="Matrix::getEnemyStep";
   trace->event(s_fn,0,"enter");
	
	int step = (int) (rand() % stepFactor)+minStep;
	
	trace->event(s_fn,0,"leave [step=%d]",step);
	return step;
}

/**
 * Get enemy delay between monsters
 * @return enemy delay value
 */
int Matrix::getEnemyDelay( void )
{	
	const char *s_fn="Matrix::getEnemyDelay";
   trace->event(s_fn,0,"enter");
	
	trace->event(s_fn,0,"leave [enemyDelay=%d]",enemyDelay);
	return enemyDelay;
}

/** 
 * Calculate delay between two wave.
 * @return delay between two waves
 */
int Matrix::getWaveDelay( void )
{	
   const char *s_fn="Matrix::getWaveDelay";
   trace->event(s_fn,0,"enter");
	
	trace->event(s_fn,0,"leave [waveDelay=%d]",waveDelay);
	return waveDelay;
}

/**
 * Calculate how much monster will be in a wave
 * @return amount of start cash
 */
int Matrix::getStartCash( void )
{
	const char *s_fn="Matrix::getStartCash";
   trace->event(s_fn,0,"enter");
	
	int cash=0;
	
	switch (level)
	{
		case gameEasy:   cash=START_CASH_EASY;
							  break;

		case gameMedium: cash=START_CASH_MEDIUM;
							  break;							
							  
		case gameHard:   cash=START_CASH_HARD;
							  break;	
	}
	
	trace->event(s_fn,0,"leave [cash=%d]",cash);
	return cash;
}
	
// ------------------------------
// Setters
// ------------------------------

/** 
 * Set wave value 
 * @param wave1 	Set wave1 value.
 */
void Matrix::setWave( int wave1 )
{
	const char *s_fn="Matrix::setWave";
   trace->event(s_fn,0,"%d",wave1);
	
	wave=wave1;
	calculateMatrix();
}

/**
 * Set level
 * @param level1	The selected level [easy, medium, hard]
 */
void Matrix::setLevel( int level1 )
{
   const char *s_fn="Matrix::setLevel";
   trace->event(s_fn,0,"%d", level);
	
	level=level1;
}

// ------------------------------
// The end
// ------------------------------
