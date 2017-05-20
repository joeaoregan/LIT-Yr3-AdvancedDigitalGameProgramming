/*
    PlayState.cpp
    SDL Game Programming Book
  
    Created by shaun mitchell on 09/02/2013.
    Copyright (c) 2013 shaun mitchell. All rights reserved.
	
	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/22	Pressing the Pause button on gamepad (button 7 on NVidia controller) pauses the game
					Increased screen size, and created viewport at bottom of screen to render lives, level, timer, and score
		2017/04/16	Added Timer class to handle the countdown clock, replacing the game timer function
		2017/		Added High Scores update function to store the name and score at the end of the game to an
					external file holding a list of 10 names and scores scores.txt
		2017/02/07	Added game timer function in PlayState, to keep track of the seconds passed since the game / level started
					using SDL_GetTicks() to get time and loadFromRenderedtext in TextureManager to render text to texture
*/

#include <iostream>
#include <fstream>
#include "PlayState.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "Level.h"
#include "BulletHandler.h"
#include "Timer.h"					// 2017/04/16 Timer class for creating a game clock

GameObject* clock1 = new Timer();	// 2017/04/16 Timer for game

const std::string PlayState::s_playID = "PLAY";
std::stringstream timeText;
bool nameEntered = true;			// 2017/04/22 Test --> set false for entering name

//unsigned int lastTime = 0, currentTime, gameTimer = 0;

SDL_Rect gameViewport;				// 2017/04/22 Main game screen view port, this is the section of the window where the game is rendered
SDL_Rect statusViewport;

void PlayState::update() {
    if(m_loadingComplete && !m_exiting)     {
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))         {
            TheGame::Instance()->getStateMachine()->pushState(new PauseState());
        }
        
        if(TheInputHandler::Instance()->getButtonState(0, 7))							// 2017/04/22	Uncommented. Button 7 is pause on NVidia controller
        {
            TheGame::Instance()->getStateMachine()->pushState(new PauseState());
        }
    
        TheBulletHandler::Instance()->updateBullets();
        
        if(TheGame::Instance()->getPlayerLives() == 0) {
			nameEntered = false;
			highScoreUpdate(TheGame::Instance()->getPlayerName(), Game::Instance()->getScore());
            TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
        }
        
        if(pLevel != 0) {
            pLevel->update();
        }
    }
}

/*
	HighScoreUpdate()

	This function takes a name and score, adds it to the maximum 10 names and scores stored in an external text file
	The function reads the scores.txt file and stores up to 10 player names and scores in a struct PlayerScores
	All 11 names and scores are added to an array of structs scoresTable first reading in the 10 stored then
	adding the name and score passed to the function at the end of the array
	The scores are then sorted and the best 10 are wrote back to the scores file

*/
void PlayState::highScoreUpdate(std::string name, int score) {
	std::cout << name << " " << score << std::endl;				// Output name and score passed to function to console window

	const int numScores = 10;									// Number of players names & scores to store
	int eachScore = 0;
	std::string scoreString;

	std::ifstream infile;	
	infile.open("scores.txt");

	std::cout << "Reading high scores from file" << std::endl;

	struct PlayerScores {		// Structure to hold High Scores deetails
		std::string name;		// Players name
		int score;				// Player score
	};

	PlayerScores temp;			// Temp struct to swap score positions

	PlayerScores scoreTable[11];// Array of structs to hold player names & scores
	//for (int i = 0; i < 11; i++) {
	//	scoreTable[i] = { "", 0 };
	//}

	// Get the existing scores from the score.txt file
	if (infile.is_open()) {
		while (getline(infile, scoreTable[eachScore].name) && getline(infile, scoreString) && eachScore <= numScores) {
			scoreTable[eachScore].score = stoi(scoreString);
			++eachScore;

			std::cout << "eachScore: " << eachScore << std::endl;
		}

		infile.close();
	}

	std::cout << "eachScore before adding score to array " << eachScore << std::endl;
	
	// Add the current score to the end of the array
	scoreTable[eachScore].name = name;		// Up to 11th position
	scoreTable[eachScore].score = score;	

	std::cout << "name added: " << scoreTable[eachScore].name << " score added " << scoreTable[eachScore].score << std::endl;

	// Sort the structure
	for (int i = 1; i < eachScore + 1; i++) {
		for (int j = 0; j < eachScore + 1 - i; j++) {
			if (scoreTable[j].score < scoreTable[j + 1].score) { // Sort Largest Score To Smallest in the struct
				temp = scoreTable[j];
				scoreTable[j] = scoreTable[j + 1];
				scoreTable[j + 1] = temp;
			}
		}
	}

	if (eachScore < 10) eachScore++; // display extra score if less than 10

	// Write back to scores file
	std::ofstream outfile;			// Create stream to write to file
	outfile.open("scores.txt");		// Open file to write to

	for (int i = 0; i < eachScore; i++) {
		outfile << scoreTable[i].name << std::endl << scoreTable[i].score << std::endl;	// Write the Names and Scores to file
	}
}

//std::string inputText = "Name";	// 2017/04/22 Name entered now stored in Game.h
//bool quit = false;
unsigned int readyTextTimer;
//bool renderText;
//SDL_Event event;

void PlayState::render() {
	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &gameViewport);									// 2017/04/22 Set the viewport to Game Screen
	/*
	if (!nameEntered) {																						// If a name hasn't already been entered
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x00, 0x00, 0x00, 0xFF);					// Clear background
		Texture::Instance()->draw("enterNameID", 50, 100, 400, 20, Game::Instance()->getRenderer());		// Display enter name message
		Texture::Instance()->loadInputText(inputText);														// Render the input text to a texture
		Texture::Instance()->drawText("inputTextID", 50, 150, Game::Instance()->getRenderer());				// Display the input text on screen

		renderText = false;																					// flag that keeps track of whether we need to update the texture
		
		/*
		//while (SDL_PollEvent(&e) != 0) {
			//User requests quit
		if (e.type == SDL_QUIT) {
			quit = true;
		}
			//Special key input
			else if (e.type == SDL_KEYDOWN) {
				//Handle backspace
				//if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)	// backspace -> remove the last character from the string
				if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_BACKSPACE) && inputText.length() > 0)
				{
					//lop off character
					inputText.pop_back();
					renderText = true;		// Set the text update flag
				}
				//Handle copy
				//else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)	// Ctrl + c -> copy the text to the clip board
				else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_C) && SDL_GetModState() & KMOD_CTRL)	// Ctrl + c -> copy the text to the clip board
				{
					SDL_SetClipboardText(inputText.c_str());
				}
				//Handle paste
				else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_V) && SDL_GetModState() & KMOD_CTRL)	// Ctrl + v -> get the text from the clipboard
				{
					inputText = SDL_GetClipboardText();
					renderText = true;		// Set the text update flag
				}
				else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
					TheGame::Instance()->setName(inputText);
					nameEntered = true;
				}
			}
			
			//Special text input event
			else if (e.type == SDL_TEXTINPUT) {
				//Not copy or pasting
				if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
					//Append character
					inputText += e.text.text;
					renderText = true;
					readyTextTimer = SDL_GetTicks();
				}
			}
			
		//}
		*/
		/*		
		while (SDL_PollEvent(&event) != 0) {
			//User requests quit
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			//Special key input
			else if (event.type == SDL_KEYDOWN) {
				//Handle backspace
				if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)	// backspace -> remove the last character from the string
				{
					//lop off character
					inputText.pop_back();
					renderText = true;		// Set the text update flag
				}
				//Handle copy
				else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)	// Ctrl + c -> copy the text to the clip board
				{
					SDL_SetClipboardText(inputText.c_str());
				}
				//Handle paste
				else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)	// Ctrl + v -> get the text from the clipboard
				{
					inputText = SDL_GetClipboardText();
					renderText = true;		// Set the text update flag
				}
				else if (event.key.keysym.sym == SDLK_RETURN) {
					TheGame::Instance()->setPlayerName(inputText);							// Set the Players name for high scores
					nameEntered = true;
				}
			}
			//Special text input event
			else if (event.type == SDL_TEXTINPUT) {
				//Not copy or pasting
				if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
					//Append character
					inputText += event.text.text;
					renderText = true;
					readyTextTimer = SDL_GetTicks();
				}
			}
		}
				
		if (renderText) {																	// Rerender text if needed			
			if (inputText != "") {															// If the input text is not empty				
				//gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColor);
				Texture::Instance()->loadInputText(inputText);								// Render new text
			}
			//Text is empty
			else {
				//Render space texture
				//gInputTextTexture.loadFromRenderedText(" ", textColor);					// Can't render an empty string, so has to be space
				Texture::Instance()->loadInputText(" ");									// Has to be something in the string to render it
			}
		}
	}
	else if(nameEntered){
		*/
		if (m_loadingComplete) {
			if (pLevel != 0) {
				pLevel->render();
			}

			// Display ready message for 2.5 seconds
			if (SDL_GetTicks() < readyTextTimer + 2500) {
				Texture::Instance()->loadReadyText("Get Ready " + Game::Instance()->getPlayerName());
				Texture::Instance()->drawText("readyID", 210, 190, Game::Instance()->getRenderer());
			}

			//gameTimer();	// Calculate and display the game timer
			clock1->update();	// 2017/04/16 Timer update function

			//TheTextureManager::Instance()->loadFromRenderedText("Level 1", "testxxx", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), TheGame::Instance()->getRenderer());		// Lives in top left corner
			
			TheBulletHandler::Instance()->drawBullets();

			// 2017/04/22 Game info viewport
			SDL_RenderSetViewport(Game::Instance()->getRenderer(), &statusViewport);				// 2017/04/22 Set the viewport to Game Screen

			// Draw Lives
			for (int i = 0; i < TheGame::Instance()->getPlayerLives(); i++) {
				TheTextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
			}
			
			// Display Level Number
			//Texture::Instance()->loadLevelText("Level 1", TheGame::Instance()->getRenderer());
			Texture::Instance()->loadLevelText("Level " + std::to_string(Game::Instance()->getCurrentLevel()));	// 2017/04/22 Changed to show current level number
			Texture::Instance()->drawText("levelID", 120, 0, TheGame::Instance()->getRenderer());

			// Display Timer
			// id, x, y, width, height, currentRow, currentFrame, pRenderer, angle, alpha, flip
			Texture::Instance()->drawFrame("timerID", 300, 0, 150, 30, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
			//TheTextureManager::Instance()->drawText("testxxx", 100, 100, TheGame::Instance()->getRenderer());

			SDL_RenderSetViewport(Game::Instance()->getRenderer(), NULL);				// 2017/04/22 Set the viewport to Game Screen
		}
    //}

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), NULL);					// Clear View Port
}

bool PlayState::onEnter() {
	Game::Instance()->setEnterTextState(false);	// 2017/04/22 

	gameViewport = { 0, 0, 800, 480 };		// 2017/04/22 Set view port x, y, w, h
	statusViewport = { 0, 480, 800, 30 };	// 2017/04/22 Set view port x, y, w, h

    TheGame::Instance()->setPlayerLives(3);
		    
    LevelParser levelParser;
    pLevel = levelParser.parseLevel(TheGame::Instance()->getLevelFiles()[TheGame::Instance()->getCurrentLevel() - 1].c_str());

	// Input Text
	readyTextTimer = SDL_GetTicks();
	//renderText = true;
	nameEntered = false;	// Input a name

	Texture::Instance()->loadEnterNameText("Please Enter Your Name:");			// Render message indicating to enter name
    
    TheTextureManager::Instance()->load("assets/bullet1.png", "bullet1", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("assets/bullet2.png", "bullet2", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/bullet3.png", "bullet3", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("assets/bullet4.png", "bullet4", Game::Instance()->getRenderer());				// 2017/03/14 Angry glider bullet
	TheTextureManager::Instance()->load("assets/lives.png", "lives", TheGame::Instance()->getRenderer());		// Lives in top left corner
	//bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* rend, bool textWrapped = false);
	//TheTextureManager::Instance()->load("assets/lives.png", "test", TheGame::Instance()->getRenderer());		// Lives in top left corner
	//TheTextureManager::Instance()->loadFromRenderedText("Level 1", "testxxx", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), TheGame::Instance()->getRenderer());		// Lives in top left corner
    
    if(pLevel != 0) {
        m_loadingComplete = true;
    }

    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit() {
    m_exiting = true;
    
    TheInputHandler::Instance()->reset();
    TheBulletHandler::Instance()->clearBullets();

	//gameTimer = 0;
    
    std::cout << "exiting PlayState\n";
    return true;
}

/*
	gameTimer()

	This function calculates and renders to texture the time in seconds using SDL_GetTicks() to get time
	and loadFromRenderedtext in TextureManager to render text to texture

void PlayState::gameTimer() {
	timeText.str("");						// Clear the timer

	currentTime = SDL_GetTicks();			// Set the current time

	if (currentTime > lastTime + 1000) {	// Every 1 second (1000ms)
		lastTime = currentTime;				// Set last time to existing time

		gameTimer++;					// Increment countdown timer

		std::cout << "Timer: " << gameTimer << std::endl;
	}

	Game::Instance()->setScore(gameTimer);

	timeText << "Time: " << gameTimer;	// Set the game timer

	TheTextureManager::Instance()->loadScoreText(timeText.str().c_str(), TheGame::Instance()->getRenderer());	// Player Score
	//TheTextureManager::Instance()->loadFromRenderedText(timeText.str().c_str(), "timer", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 12), TheGame::Instance()->getRenderer());		// Lives in top left corner
}
*/