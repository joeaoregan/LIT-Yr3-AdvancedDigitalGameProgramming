/*
	LevelObjectiveState.cpp

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/25	Created Level objective state, to inform player killing 7 turrets = points bonus for Level 1, other objectives can be added
					After entering name, the name would have been displayed in a custom mission objective, but text rendering was an issue here, 
					no time to replace the full Texture Manager class

					The button presses don't clear, keeping all the input handling together in the Input Handler probably would have helped
*/

#include <iostream>
#include "MainMenuState.h"			// Objective can return to Menu State
#include "LevelObjectiveState.h"
#include "PlayState.h"				// Objective automatically moves to Play State
#include "TextureManager.h"
#include "Game.h"	
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string LevelObjectiveState::s_ObjectiveID = "OBJECTIVE";

void LevelObjectiveState::s_objectiveToMenu() {
	Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void LevelObjectiveState::s_objectiveToGame() {
	Game::Instance()->getStateMachine()->changeState(new PlayState());	// Add the Play State and start the game
}

void LevelObjectiveState::update() {
	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->update();
		}
	}

	if (!buttonPressed()) {													// If a buttons not pressed
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE) ||		// If Esc key
			InputHandler::Instance()->isKeyDown(SDL_SCANCODE_BACKSPACE)) {	// Or Backspace
			s_objectiveToMenu();											// Exit the game

			setButtonPressed();												// Disable ability to press button, and time before button can be pressed again
		}
		//if (SDL_GetTicks() > btnTimer + 2000) {								// Wait 2 seconds before allowing the game to continue, to show my name in all its magnificance
			if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN) ||	// If Enter
				InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) ||	// Or Spacebar
				InputHandler::Instance()->getButtonState(0, 0)) {			// Or gamepad button A
				s_objectiveToGame();										// Skip objectives and proceed to Game

				setButtonPressed();											// Disable ability to press button, and time before button can be pressed again
			}			
		//}
	}

	// Leave 3 seconds before proceeding to Game
	if (SDL_GetTicks() > btnTimer  + 3000) {								// If time is greater than 3 seconds
		s_objectiveToGame();												// Proceed to the Play State
	}
}

void LevelObjectiveState::render() {
	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->draw();
		}
	}

	//std::cout << "Difficulty: " << Game::Instance()->getDifficulty() << std::endl;

	if (Game::Instance()->getDifficulty() == 0) Texture::Instance()->draw("l1objeasy", 0, 0, 800, 640, Game::Instance()->getRenderer());			// Label Easy
	else if (Game::Instance()->getDifficulty() == 1) Texture::Instance()->draw("l1objmed", 0, 0, 800, 640, Game::Instance()->getRenderer());		// Label Normal
	else if (Game::Instance()->getDifficulty() == 2) Texture::Instance()->draw("l1objhard", 0, 0, 800, 640, Game::Instance()->getRenderer());		// Label Hard
	
	Texture::Instance()->draw("l1objhard", 0, 800, 640, 50, Game::Instance()->getRenderer());		// Label Hard
}

bool LevelObjectiveState::onEnter() {
	setButtonPressed();																				// Disable ability to press button, and time before button can be pressed again

	StateParser stateParser;
	stateParser.parseState("assets/attack.xml", s_ObjectiveID, &m_gameObjects, &m_textureIDList);	// Load objective assets
	
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_objectiveToMenu);														// Callback 1. Proceed to Main Menu (button)

	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "Entering Instructions State\n";
	return true;
}

bool LevelObjectiveState::onExit() {
	m_exiting = true;

	pressed = true;
	btnTimer = 0;

	InputHandler::Instance()->reset();			// Reset Input Handler
	m_textureIDList.clear();					// Clear Texture list

	std::cout << "Exiting Titles State\n";

	return true;
}

void LevelObjectiveState::setCallbacks(const std::vector<Callback>& callbacks) {
	if (!m_gameObjects.empty()) {													// go through the game objects
		for (int i = 0; i < m_gameObjects.size(); i++) {			
			if (dynamic_cast<MenuButton*>(m_gameObjects[i])) {						// if they are of type MenuButton then assign a callback based on the id passed in from the file
				MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
		}
	}
}

