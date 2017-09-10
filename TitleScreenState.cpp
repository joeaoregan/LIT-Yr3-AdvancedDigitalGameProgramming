/*
	TitleScreenState.cpp

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/24	Created Title Screen State because I deserve credit for everything (and a small bit Shaun Mitchell)
*/

#include <iostream>
#include "TitleScreenState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string TitleScreenState::s_TitleID = "TITLE";

void TitleScreenState::s_titleToMenu() {
	Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void TitleScreenState::s_exitFromTitle() {
	TheGame::Instance()->quit();
}

void TitleScreenState::update() {
	/*
		If the Esc, Backspace or gamepad B button is pressed, return to main menu
	*/
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE) ||		// If Esc key
		InputHandler::Instance()->isKeyDown(SDL_SCANCODE_BACKSPACE)) {	// Or Backspace
		s_exitFromTitle();												// Exit the game
	}

	// Leave 2 seconds before allowing a button press to proceed to Main Menu
	if (SDL_GetTicks() > btnTimer + 2000) {								// Wait 2 seconds before allowing the game to continue, to show my name in all its magnificance
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN) ||	// If Enter
			InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) ||	// Or Spacebar
			InputHandler::Instance()->getButtonState(0, 0)) {			// Or gamepad button A
			s_titleToMenu();											// Return to main menu
		}

		if (m_loadingComplete && !m_gameObjects.empty()) {
			for (int i = 0; i < m_gameObjects.size(); i++) {
				m_gameObjects[i]->update();
			}
		}
	}
	// Leave 10 seconds before proceeding to Main Menu
	if (SDL_GetTicks() > btnTimer  + 10000) {							// If time is greater than 10000
		s_titleToMenu();												// Proceed to the Main Menu
	}
}

void TitleScreenState::render() {
	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->draw();
		}
	}
}

bool TitleScreenState::onEnter() {
	StateParser stateParser;
	stateParser.parseState("assets/attack.xml", s_TitleID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_titleToMenu);								// Proceed to Main Menu

	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "Entering Instructions State\n";
	return true;
}

bool TitleScreenState::onExit() {
	m_exiting = true;

	InputHandler::Instance()->reset();			// Reset Input Handler
	m_textureIDList.clear();					// Clear Texture list

	std::cout << "Exiting Titles State\n";

	return true;
}

void TitleScreenState::setCallbacks(const std::vector<Callback>& callbacks) {	
	if (!m_gameObjects.empty()) {													// go through the game objects
		for (int i = 0; i < m_gameObjects.size(); i++) {			
			if (dynamic_cast<MenuButton*>(m_gameObjects[i])) {						// if they are of type MenuButton then assign a callback based on the id passed in from the file
				MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
		}
	}
}

