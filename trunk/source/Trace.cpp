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
#include "trace.h"

// Enable / Disable trace file functionality
bool traceOn = false;

// ------------------------------
// Constructor
// ------------------------------

Trace::Trace()
{
	fp=NULL;
}

// ------------------------------
// Destructor
// ------------------------------

Trace::~Trace()
{
  close();
}

// ------------------------------
// Methods
// ------------------------------

// Open trace file
int Trace::open(const char *filename)
{
   int returnValue=0;
   
   if (!traceOn) return -1;
         
   if((fp=fopen(filename, "wb"))==NULL) 
   {
      printf("Error: Cannot open trace file.\n");
      returnValue=-2;
   }   
   return returnValue;
}


// Close trace file
int Trace::close()
{
   int returnValue=0;
   
   if (fp!=NULL)
   {
       fclose(fp);
   }	
   return returnValue;
}


// Create trace timestamp
char * Trace::getDate()
{
  struct tm *now = NULL;
  time_t time_value = 0;
  static char buf[ 128 ] ;
  
  // Clear memory  
  memset(buf, sizeof(buf), 0x00);
  
  /* Get time value */
  time_value = time(NULL);          
  
  /* Get time and date structure */
  now = localtime(&time_value);     

  // Create time stamp
  sprintf(buf,"%02d-%02d-%04d %02d:%02d:%02d",
	now->tm_mday, now->tm_mon+1, now->tm_year+1900, 
	now->tm_hour,now->tm_min,now->tm_sec);
	
  return buf;
}

// Save trace event in trace file
int Trace::event( const char *functionName, int threadNr, const char *event, ...)
{
   int returnValue=0;
   char buf[ MAX_LEN ];
   
   // Clear memory  
   memset(buf, MAX_LEN, 0x00);
   
   if (!traceOn) return -1;
   
   // Expend event string
   va_list list;
   va_start(list, event );
   vsprintf(buf, event, list);
   
   if (fp!=NULL)
   {
      // Save string to file
	  fprintf(fp,"%s [thread%d-%s] %s\n",getDate(), threadNr, functionName, buf); 
	  fflush(fp); 
   }
   
   return returnValue;
}


// Save trace event in trace file
int Trace::eventRaw( char character)
{
   int returnValue=0;
   
   if (!traceOn) return -1;
     
   if (fp!=NULL)
   {
      // Save string to file
	  fprintf(fp,"%c",character); 
	  fflush(fp); 
   }
   
   return returnValue;
}


// ------------------------------
// The end
// ------------------------------