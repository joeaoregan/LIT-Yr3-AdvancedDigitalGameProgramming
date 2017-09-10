/*
	HighScoreState.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Original health bar code:
	https://forums.libsdl.org/viewtopic.php?t=11040&sid=0c796abe9954dba84ee2814c32c85f5c

	Done:
		2017/04/22	Added Status Bar header file
*/

#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <SDL_image.h>
#include "Game.h"

#define MAX_HEALTH 100.0		// The max health for a player
#define START_LEFT 0			// Move status bar left to right
#define START_RIGHT 1			// Move status bar right to left

enum healthBarOrientation { VERTICAL, HORIZONTAL };

class StatusBar {
public:
	StatusBar() {};													// Constructor
	~StatusBar() {};												// Destructor

	/* VARIABLES */

	//float startTime = 3.0;										// Start time for countdown timer bars
	//float endTime = 0.0;											// End time for countdwown timer bars

	SDL_Color fgColour = { 0, 255, 0, 255 };						// Set bar foreground colour as green
	//SDL_Color fgColourBlue = { 0, 200, 255, 255 };				// Set bar foreground colour as Blue
	SDL_Color bgColour = { 255, 0, 0, 255 };						// Set bar background colour as red
	//SDL_Color bgColourOrange = { 255, 150, 0, 255 };				// Set bar background colour as Orange
	//SDL_Color bgColourBlue = { 0, 0, 255, 255 };					// Set bar background colour as Blue

	/* FUNCTIONS */

	void createStatusBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, int orientation, int startFrom = START_LEFT) {	// Horizontal healthbar 2017/01/20 added if statement to decide orientation of health bar
		SDL_Rect foregroundRect;																				// The rectangle representing the percentage
		Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
		SDL_Color old;																							// Store the previous draw colour
		SDL_GetRenderDrawColor(Game::Instance()->getRenderer(), &old.r, &old.g, &old.g, &old.a);				// Get the previous render draw colour and store it
		SDL_Rect backgroundRect = { x, y, w, h };																// Background rectangle with coordinates and dimensions entered
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), BGColor.r, BGColor.g, BGColor.b, BGColor.a);	// Set the colour
		SDL_RenderFillRect(Game::Instance()->getRenderer(), &backgroundRect);									// Draw a Solid Rectangle with the RGB colour values assigned for background
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), FGColor.r, FGColor.g, FGColor.b, FGColor.a);	// Set the foreground rectangle colour
		
		// Decide if Healthbar is horizontal or vertical
		if (orientation == HORIZONTAL) {											// Horizontal bar
			int newW = (int)((float)w * Percent);									// new width
			int newX = x + (w - newW);												// new x coord
			if (startFrom == START_LEFT) foregroundRect = { newX, y, newW, h };		// Decrease from left
			else if (startFrom == START_RIGHT) foregroundRect = { x, y, newW, h };	// 2017/02/17 Decrease from right
		}
		else if (orientation == VERTICAL) {											// Verical bar
			int ph = (int)((float)h * Percent);
			int py = y + (h - ph);
			foregroundRect = { x, py, w, ph };
		}

		SDL_RenderFillRect(Game::Instance()->getRenderer(), &foregroundRect);					// Draw a solid rectangle
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), old.r, old.g, old.b, old.a);	// Reset the previous draw colour
	}
	
	// Custom functions for various status bars
	void playerHealthBar(int x, int y, int w, float Percent) {
		createStatusBar(x + (w / 4), y - 10, w / 2, 5, Percent / MAX_HEALTH, fgColour, bgColour, HORIZONTAL);	// -10 Places 10 pixels above Player Ship
	}
	//void enemyBossBar(float health);								// 2017/03/18 Added Bar for Enemy Boss
};

#endif