/*
	Timer.h

	Created by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/16	Added Timer class to replace gameTimer() in PlayState.cpp
*/

#ifndef TIMER_H
#define TIMER_H

//#include "_TestData.h"
#include "GameObject.h"
#include <sstream>					// For timer
#include "Game.h"
//#include "TextureManager.h"

//const static int GAME_TIMER = 50;					// 2017/04/16 Not needed clock counts up not down

class Timer : public GameObject {
public:
	// Constructor
	Timer() {
		std::cout << "Timer created" << std::endl;

		//setCountDownTimer(GAME_TIMER);			// 2017/04/16 Not needed clock counts up not down
		lastTime = 0;

		setName("TIMER");
		setTextureID("timerID");
		//setType(TIMER);
		//setAlive(true);	// 2017/04/16 Not needed already a variable m_bDead for checking if Game Object is alive or not
		m_bDead = false;	//2017/04/16 Set object alive
	}

	~Timer() {
		std::cout << getName() << " destroyed!!!" << std::endl;
	}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams) {};

	// Update the timer
	//virtual void move(int x = 0, int y = 0) {								// 2017/04/12
	virtual void update() {													// 2017/04/16
		timeText.str("");

		currentTime = SDL_GetTicks();										// Get the current game running time

		if (currentTime > lastTime + 1000) {								// Decrement countdown timer
			/*gTimeTextTexture.renderTextToTexture(timeText.str().c_str(), { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));
			//gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, SDL_Renderer* pRenderer, bool textWrapped) {
			//TheTextureManager::Instance()->loadFromRenderedTex(gTimeTextTexture, timeText.str().c_str(), "TimerID");
			
			//Texture::Instance()->loadScoreText(timeText.str().c_str(), Game::Instance()->getRenderer());	// Player Score
			*/
			lastTime = currentTime;											// Store this time
			gameTimer++;													// Increment the timer
		}

		Game::Instance()->setScore(gameTimer);

		timeText << "Time: " << gameTimer;									// Set the game timer
		
		Texture::Instance()->loadTimerText(timeText.str().c_str());			// The game time
	};

	// Draw the timer
	//void render() {
	virtual void draw() {															// 2017/04/16
		if (currentTime > lastTime + 1000) {								// Decrement countdown timer
			std::cout << "Test Timer: " << gameTimer << " lastTime: " << lastTime << " currentTime: " << currentTime << std::endl;	// display timer in console window
		}

		//gTimeTextTexture.render(SCREEN_WIDTH - gTimeTextTexture.getWidth() - 10, 8);						// Draw on screen
		// REPLACE WITH DRAW FUNCTION
	};

	// Destroy the timer
	//void destroy() {
	virtual void clean() {															// 2017/04/16
		//std::cout << "Timer destroy" << std::endl;

		//setCountDownTimer(GAME_TIMER);
	};



	virtual void collision() {}							// 2017/04/16 Needed for a Game Object

	virtual std::string type() { return "Timer"; }		// 2017/04/16 Needed for a Game Object


	unsigned int getCountdownTimer() { return gameTimer; }						// Returns the current game time
	void setCountDownTimer(unsigned int t) { gameTimer = t; }					// 2017/04/13 Set bonus times etc

private:
	std::stringstream timeText;
	int gameTimer;
	unsigned int lastTime, currentTime;	// TEST TIMING
	//Texture gTimeTextTexture;
};

#endif
