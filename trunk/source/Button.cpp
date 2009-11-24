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
#include <stdlib.h>
#include <string.h>

#include "General.h"
#include "GRRLIB.h"
#include "Button.h"

Button::Button()
{
   x=0;
   y=0;	
   height=0;
   width=0;
}


Button::Button(int x1,int y1, GRRLIB_texImg imageNormal1, GRRLIB_texImg imageFocus1 )
{
   x = x1;
   y = y1;
   imageNormal=imageNormal1;
   imageFocus=imageFocus1;
}
	
// ------------------------------
// Destructor
// ------------------------------

Button::~Button()
{
  
}

// ------------------------------
// Others
// ------------------------------

void Button::setImageNormal(GRRLIB_texImg imageNormal)
{

}

void Button::setImageSelect(GRRLIB_texImg imageFocus)
{

}
		
void Button::setX(int x1)
{
   if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
   {
      x = x1;
   }
}

int Button::getX()
{
	return x;
}

void Button::setY(int y1)
{
   if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
   {
      y = y1;
   }
}

int Button::getY()
{
	return y;
}

	