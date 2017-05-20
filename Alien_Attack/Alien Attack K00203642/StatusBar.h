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

#define MAX_HEALTH 100.0		// The max health for a Player, and Enemy Boss
#define TURRET_HEALTH 15		// The max health for a Turret
#define START_LEFT 0			// Move status bar left to right
#define START_RIGHT 1			// Move status bar right to left

enum healthBarOrientation { VERTICAL, HORIZONTAL };

class StatusBar {
public:
	StatusBar() {};								// Constructor
	~StatusBar() {};							// Destructor

	/* VARIABLES */

	//float startTime = 3.0;					// Start time for countdown timer bars
	//float endTime = 0.0;						// End time for countdwown timer bars

	SDL_Color barGreen = { 0, 255, 0, 255 };	// Set bar foreground colour as green for Player
	SDL_Color bossFG = { 170, 189, 159, 255 };	// Set bar foreground colour as grey for Boss
	SDL_Color bossBG = { 153, 55, 41, 255 };	// Set bar background colour as grey for Boss
	SDL_Color barBlue = { 0, 200, 255, 255 };	// Set bar foreground colour as Blue for Turret
	SDL_Color barRed = { 255, 0, 0, 255 };		// Set bar background colour as red for Player
	SDL_Color barOrange = { 255, 150, 0, 255 };	// Set bar foreground colour as Orange for Roof Turret
	SDL_Color barGrey = { 81, 82, 81, 255 };	// Set bar foreground colour as Dark Grey for eskeletor

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
		createStatusBar(x + (w / 4), y - 10, w / 2, 5, Percent / MAX_HEALTH, barGreen, barRed, HORIZONTAL);		// 2017/04/22 Player Health Bar function
	}
	void turretHealthBar(int x, int y, int w, float Percent) {
		createStatusBar(x + (w / 4), y - 10, w / 2, 5, Percent / TURRET_HEALTH, barBlue, barRed, HORIZONTAL);	// 2017/04/22 Turret Health Bar function
	}
	void rTurretHealthBar(int x, int y, int w, float Percent) {
		createStatusBar(x + (w / 4), y - 10, w / 2, 5, Percent / TURRET_HEALTH, barOrange, barRed, HORIZONTAL);	// 2017/04/22 RoofTurret Health Bar function
	}
	void bossBar(int x, int y, float Percent) {
		createStatusBar(x + 180, y + 65, 5, 100, Percent / MAX_HEALTH, bossFG, bossBG, VERTICAL);				// 2017/04/22 Enemy Boss Health Bar function with coordinate offsets
	}
	void eHeManBar(int x, int y, float Percent) {
		createStatusBar(x, y - 10, 34, 5, Percent / 3, barGrey, bossBG, HORIZONTAL);							// 2017/04/22 Eskeletor Health Bar function with coordinate offsets
	}
};

#endif