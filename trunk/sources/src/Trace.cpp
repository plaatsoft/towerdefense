/** 
 *  @file 
 *  @brief The file contains the Trace class
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

/**
 * Constructor
 * Init all properties with default values.
 */
Trace::Trace()
{
	fp=NULL;
}

// ------------------------------
// Destructor
// ------------------------------

/**
 * Destructor
 * Clean up all allocated memory
 */
Trace::~Trace()
{
  close();
}

// ------------------------------
// Methods
// ------------------------------

/**
 * Open trace file.
 *
 * @param filename		The trace filename
 *
 * @return error code [0 ok, -1 error]
 */
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

/**
 * Close trace file
 */
 
void Trace::close()
{
   if (fp!=NULL)
   {
       fclose(fp);
   }	
}

/**
 * Create trace timestamp
 *
 * @return timestamp in dutch format
 */
char * Trace::getDate()
{
  struct tm *now = NULL;
  time_t time_value = 0;
  static char buf[ 20 ] ;
   
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

/**
 * Log trace event to trace file
 *
 * @param functionName	The function name
 * @param threadNr		The threadnr [0=main thread, 1=network thread]
 * @param event			The event description
 * @param ...				Other parameters
 *
 * @return error code [0 ok, -1 error]
 */
int Trace::event( const char *functionName, int threadNr, const char *event, ...)
{
   int returnValue=0;
   char buf[ MAX_LEN ];

   if (!traceOn) return -1;
   
   // Clear memory  
   memset(buf, MAX_LEN, 0x00);
      
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

/**
 * log raw (hex) character to trace file
 *
 * @param character 	The raw data character.
 *
 * @return error code [0=ok, -1=error]
 */
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