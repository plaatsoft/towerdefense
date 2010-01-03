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


// ------------------------------
// Constructor
// ------------------------------

Matrix::Matrix()
{
	wave=0;
}

// ------------------------------
// Destructor
// ------------------------------

Matrix::~Matrix()
{
}

// ------------------------------
// Methods
// ------------------------------

// ------------------------------
// Getters
// ------------------------------

// Calculate how much monster will be in a wave
int Matrix::getEnemyAmount( void )
{
	// Calculate how much monster will be in the wave
	int amount=4+wave;
	if (amount>90) amount=90;
	
	return amount;
}

// Get enemy step size
int Matrix::getEnemyStep( void )
{
	// Increase step each 20 waves
	int step = (int) (rand() % ((wave/20)+1))+1;
	return step;
}

// Get enemy delay 
int Matrix::getEnemyDelay( void )
{
	// Calculate delay between two monsters.
	int delay=wave*3;
	
	if (delay>90) delay=90+(wave/20);
	if (delay>95) delay=95;

	return delay;
}

// Get wave delay 
int Matrix::getWaveDelay( void )
{
	// Calculate delay between two monsters.
	int delay=wave*3;
	
	if (delay>90) delay=90+(wave/20);
	if (delay>95) delay=95;

	return delay;
}

// ------------------------------
// Setters
// ------------------------------

// Set wave value
void Matrix::setWave( int wave1 )
{
	wave=wave1;
}

// ------------------------------
// The end
// ------------------------------
