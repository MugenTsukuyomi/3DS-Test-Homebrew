/*
	Both Screen Text example made by Aurelio Mannara for ctrulib
	This code was modified for the last time on: 12/12/2014 23:20 UTC+1

*/

#include <3ds.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	// Initialize services
	gfxInitDefault();

	// We need these 2 buffers for APT_DoAppJump() later.
	u8 param[0x300];
	u8 hmac[0x20];

	// Loop as long as the status is not exit
	while (aptMainLoop())
	{
		// Scan hid shared memory for input events
		hidScanInput();

		if (hidKeysDown() & KEY_A) // If the A button got pressed, start the app launch
		{
			// Clear both buffers
			memset(param, 0, sizeof(param));
			memset(hmac, 0, sizeof(hmac));

			// Prepare for the app launch
			APT_PrepareToDoApplicationJump(0, 0x0004001000022400LL, 0); // *EUR* camera app title ID
			// Tell APT to trigger the app launch and set the status of this app to exit
			APT_DoApplicationJump(param, sizeof(param), hmac);
		
		}
		//In this example we need one PrintConsole for each screen
		PrintConsole topScreen, bottomScreen;

		//Initialize console for both screen using the two different PrintConsole we have defined
		consoleInit(GFX_TOP, &topScreen);
		consoleInit(GFX_BOTTOM, &bottomScreen);



		//Before doing any text printing we should select the PrintConsole in which we are willing to write, otherwise the library will print on the last selected/initialized one
		//Let's start by printing something on the top screen
		consoleSelect(&topScreen);
		printf("Diese App steht noch in Entwicklung!\n");
		printf("\x1b[20;14Hcool App...\nDruecke A um camera zu starten.");
		//Now write something else on the bottom screen
		consoleSelect(&bottomScreen);
		printf("Gibt noch nicht viel.\nIst mir aber Egal :D");

		consoleSelect(&topScreen);
		printf("\x1b[30;16HPress Start or Select to exit.");
			//Scan all the inputs. This should be done once for each frame
			hidScanInput();

			//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
			u32 kDown = hidKeysDown();


			if (kDown & KEY_START) break; // break in order to return to hbmenu
			if (kDown & KEY_SELECT) break; // break in order to return to hbmenu

			// Flush and swap framebuffers
			gfxFlushBuffers();
			gfxSwapBuffers();

			//Wait for VBlank
			gspWaitForVBlank();
		
	}
	// Exit services
	gfxExit();
	
	return 0;
}
