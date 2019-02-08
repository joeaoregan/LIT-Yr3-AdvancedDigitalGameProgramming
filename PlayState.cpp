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
#include "SoundManager.h"			// 2017/04/23 Skip music backwards and forwards

#include "Subject.h"
#include "Message.h"				// 2017/04/25 Observer

//Texture test;
Message message;

const std::string PlayState::s_playID = "PLAY";
std::stringstream timeText;

unsigned int pauseBetweenPresses = 0;
bool buttonPressed = false;

void PlayState::update() {
    if(m_loadingComplete && !m_exiting) {															// If media is loaded and the game is not exiting
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)	||							// If Esc key pressed
			InputHandler::Instance()->getButtonState(0, 6)) {										// Back button press (on Shield controller)
			if (!buttonPressed) TheGame::Instance()->getStateMachine()->pushState(new PauseState());// Pause the game, by pushing the pause state onto the list of states
			buttonPressed = true;
		}

		// 2017/04/22 Leave 1/4 of a second before the button selector moves again
		if (SDL_GetTicks() > pauseBetweenPresses + 250) {
			pauseBetweenPresses = SDL_GetTicks();													// Reset time between button presses
			buttonPressed = false;																	// Reset ability to press button
		}
    
        TheBulletHandler::Instance()->updateBullets();
        
        if(TheGame::Instance()->getPlayerLives() == 0) {
			//nameEntered = false;
			highScoreUpdate(TheGame::Instance()->getPlayerName(), Game::Instance()->getTime());		// Update the High Scores entry
            TheGame::Instance()->getStateMachine()->changeState(new GameOverState());				// Game Over
        }
        
        if(pLevel != 0) {
            pLevel->update();
        }
    }
}

unsigned int readyTextTimer;		// Time to display the Player ready message at start of level

void PlayState::render() {	
	if (m_loadingComplete) {
		if (pLevel != 0) {
			pLevel->render();
		}

		// Display ready message for 2.5 seconds
		if (SDL_GetTicks() < readyTextTimer + 2500) {
			Texture::Instance()->loadReadyText("Get Ready " + Game::Instance()->getPlayerName());
			Texture::Instance()->drawText("readyID", 250, 190, Game::Instance()->getRenderer());
		}
		
		//test.render(100, 480);

		TheBulletHandler::Instance()->drawBullets();
			
	}
}

bool PlayState::onEnter() {
	//test.renderTextToTexture("test", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));

	Game::Instance()->turretKills = 0;				// Reset turret kills

	//Texture::Instance()->loadLevelText("Level " + std::to_string(Game::Instance()->getCurrentLevel()));	// 2017/04/22 Changed to show current level number


	Texture::Instance()->load("assets/grass.png", "grass");	// Not reading from attack.xml

	Game::Instance()->setScore(0);
	Game::Instance()->totalScrolledDistance = 0.0;	// 2017/04/23 reset the scroll distance for the minimap
	Game::Instance()->setEnterTextState(false);		// 2017/04/22 
	
    TheGame::Instance()->setPlayerLives(3);

	Texture::Instance()->displayDifficulty(Game::Instance()->getDifficulty()); //2017/04/27 Display difficulty in HUD

    LevelParser levelParser;
	
	// 2017/04/25 Choose Map based on the Level Difficulty
	if (Game::Instance()->getDifficulty() == LIAM)
		pLevel = levelParser.parseLevel(Game::Instance()->getLevelFiles()[Game::Instance()->getCurrentLevel() - 1].c_str());	// Parse the level
	else if (Game::Instance()->getDifficulty() == NORMAL)
		pLevel = levelParser.parseLevel(Game::Instance()->getLevelFiles()[Game::Instance()->getCurrentLevel()].c_str());		// Parse the level
	else if (Game::Instance()->getDifficulty() == NOT_LIAM)
		pLevel = levelParser.parseLevel(Game::Instance()->getLevelFiles()[Game::Instance()->getCurrentLevel() + 1].c_str());	// Parse the level
	
	// Input Text
	readyTextTimer = SDL_GetTicks();

    if(pLevel != 0) {
        m_loadingComplete = true;
    }

	pLevel->getPlayer()->addWatcher(&message);		// 2017/04/26 Add Message to Players list of observers
	//pLevel->getPlayer()->test();


    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit() {
    m_exiting = true;
    
    TheInputHandler::Instance()->reset();
    TheBulletHandler::Instance()->clearBullets();
	
	// clear the texture manager
	for (int i = 0; i < m_textureIDList.size(); i++) {
		Texture::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	Game::Instance()->turretKills = 0;	// Reset turret kills
    


    std::cout << "exiting PlayState\n";
    return true;
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
