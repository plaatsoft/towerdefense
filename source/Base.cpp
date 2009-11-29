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

#include "General.h"
#include "grrlib.h"
#include "Base.h"
#include "Trace.h"

extern Trace trace;

// ------------------------------
// Constructor
// ------------------------------

Base::Base()
{
   const char *s_fn="Base::Base";
   trace.event(s_fn,0,"enter");

   x=0;
   y=0;	
   height=0;
   width=0;
      
   trace.event(s_fn,0,"leave");
}
	
// ------------------------------
// Destructor
// ------------------------------

Base::~Base()
{
   const char *s_fn="Base::~Base";
   trace.event(s_fn,0,"enter");
 
   
   trace.event(s_fn,0,"leave"); 
}
	
// ------------------------------
// Others
// ------------------------------

void Base::draw(void)
{   
   // Draw Base on screen
   GRRLIB_DrawImg( x, y, image, 0, 1, 1, IMAGE_COLOR );		
}

// ------------------------------
// Getters and Setters
// ------------------------------

void Base::setImage(GRRLIB_texImg *image1)
{
   const char *s_fn="Base::setImage";
   trace.event(s_fn,0,"enter");
   
   image=image1;
   
   trace.event(s_fn,0,"leave");
}
		
void Base::setX(int x1)
{
   const char *s_fn="Base::setX";
   trace.event(s_fn,0,"enter [x=%d]",x1);
   
   if ((x1>=0) && (x1<=MAX_HORZ_PIXELS))
   {
      x = x1;
   }
      
   trace.event(s_fn,0,"leave");
}

int Base::getX()
{
	return x;
}

void Base::setY(int y1)
{
   const char *s_fn="Base::setY";
   trace.event(s_fn,0,"enter [y=%d]",y1);
   
   if ((y1>=0) && (y1<=MAX_VERT_PIXELS))
   {
      y = y1;
   }
      
   trace.event(s_fn,0,"leave");
}

int Base::getY()
{
    return y;
}

// ------------------------------
// The end
// ------------------------------