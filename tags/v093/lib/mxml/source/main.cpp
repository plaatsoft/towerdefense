#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

/*Include these for mxml*/
#include <fat.h>
#include "mxml.h"

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

void CreateXmlFile(char* filename)
{
   mxml_node_t *xml;
   mxml_node_t *data;
   mxml_node_t *group;

   xml = mxmlNewXML("1.0");

   data = mxmlNewElement(xml, "screen");
  
   //Create Some config value
   mxmlElementSetAttr(data, "height","480");
   
   mxmlElementSetAttr(data, "width","640");

   //Lets do some sub items for funs
   group = mxmlNewElement(data, "properties");
   mxmlElementSetAttr(group, "username", "beardface");
  
   mxmlElementSetAttr(group, "favorite_food", "dead babies");

   /* now lets save the xml file to a file! */
   FILE *fp;
   fp = fopen(filename, "w");

   mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);
   
   /*Time to clean up!*/
   fclose(fp);
   mxmlDelete(group);
   mxmlDelete(data);
   mxmlDelete(xml);
}

void LoadXmlFile(char* filename)
{
   FILE *fp;
   mxml_node_t *tree;
   mxml_node_t *data;
   mxml_node_t *group;

   /*Load our xml file! */
   fp = fopen(filename, "r");
   tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
   fclose(fp);

   /*Load and printf our values! */
   /* As a note, its a good idea to normally check if node* is NULL */
   data = mxmlFindElement(tree, tree, "screen", NULL, NULL, MXML_DESCEND);
  
   printf("Loaded following values from xml file:\n"); 
   printf("  Height: %s\n",mxmlElementGetAttr(data,"height"));    
   printf("  Width: %s\n",mxmlElementGetAttr(data,"width"));    

   group = mxmlFindElement(tree, tree, "properties", NULL, NULL, MXML_DESCEND);
   printf("  %s's favorite food is %s\n",mxmlElementGetAttr(group, "username"), mxmlElementGetAttr(group, "favorite_food"));  

   /* Yay Done! Now lets be considerate programmers, and put memory back how
      we found it before we started playing with it...*/
   mxmlDelete(group);
   mxmlDelete(data);
   mxmlDelete(tree);
}

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

	// Initialise the video system
	VIDEO_Init();
	
	// This function initialises the attached controllers
	WPAD_Init();
	
	// Obtain the preferred video mode from the system
	// This will correspond to the settings in the Wii menu
	rmode = VIDEO_GetPreferredMode(NULL);

	// Allocate memory for the display in the uncached region
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	
	// Initialise the console, required for printf
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
	
	// Set up the video registers with the chosen mode
	VIDEO_Configure(rmode);
	
	// Tell the video hardware where our display memory is
	VIDEO_SetNextFramebuffer(xfb);
	
	// Make the display visible
	VIDEO_SetBlack(FALSE);

	// Flush the video register changes to the hardware
	VIDEO_Flush();

	// Wait for Video setup to complete
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

        /*Init Fat!*/
        fatInitDefault();

        /*MXML TEST */
        printf("Begin MXML Test...\n\n");
        printf("Creating XML Document for testing...\n");
        CreateXmlFile("test_file.xml");

        printf("Loading and Parsing test XML Document that was just created...\n");
        LoadXmlFile("test_file.xml");

        printf("\n\ntest_file.xml was created and saved to your SD card.\n\n");

        printf("Done! Press HOME to return to the HBC.\n");   
	while(1) {

		// Call WPAD_ScanPads each loop, this reads the latest controller states
		WPAD_ScanPads();

		// WPAD_ButtonsDown tells us which buttons were pressed in this loop
		// this is a "one shot" state which will not fire again until the button has been released
		u32 pressed = WPAD_ButtonsDown(0);

		// We return to the launcher application via exit
		if ( pressed & WPAD_BUTTON_HOME ) exit(0);

		// Wait for the next frame
		VIDEO_WaitVSync();
	}

	return 0;
}

