/*
	MenuState.cpp
	SDL Game Programming Book

	Created by shaun mitchell on 09/02/2013.
	Copyright (c) 2013 shaun mitchell. All rights reserved.
	
	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/03/16	Added Settings menu
*/
#include <iostream>
#include "MainMenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"

#include "EnterNameState.h"

#include "HighScoreState.h"		// Include High Scores State header file
#include "SettingsState.h"		// 2017/03/16 Include Settings State header file
#include "InstructionsState.h"	// 2017/04/24 Instructions page header
#include "InputHandler.h"
#include "StateParser.h"
#include <assert.h>

const std::string MainMenuState::s_menuID = "MENU";

/*
// Moved to MenuState.h
void setCurrentBtn(int a) {
	if (a == 0) currentBtn--;
	else if (a == 1) currentBtn++;

	if (currentBtn > 5) currentBtn = 1;
	if (currentBtn < 1) currentBtn = 5;
}
*/

// Callbacks
void MainMenuState::s_menuToPlay() {
	//TheGame::Instance()->getStateMachine()->changeState(new PlayState());		// Start the game
	Game::Instance()->getStateMachine()->changeState(new EnterNameState());		// Start the game
}

void MainMenuState::s_highScores() {	
	Game::Instance()->getStateMachine()->changeState(new HighScoreState());		// Go to high scores table
}

void MainMenuState::s_settings() {												// 2017-03-16 Added settings menu
	Game::Instance()->getStateMachine()->changeState(new SettingsState());		// Go to settings 
}

void MainMenuState::s_instructions() {											// 2017-04-24 Added instructions menu
	Game::Instance()->getStateMachine()->changeState(new InstructionsState());	// Go to instructions
}

void MainMenuState::s_exitFromMenu() {
    TheGame::Instance()->quit();
}

// end callbacks

void MainMenuState::update() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && pressed == false) {			// If spacebar is pressed - start playing game
		s_menuToPlay();
		pressed = true;
	}
	// 2017/04/22 If Return key is pressed OR gamepad button A - select current highlighted option
	else if ((InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN) || InputHandler::Instance()->getButtonState(0,0)) && pressed == false) {
		if (currentBtn == 1) s_menuToPlay();									// 1. Play Game
		else if (currentBtn == 2) s_highScores();								// 2. High Scores
		else if (currentBtn == 3) s_settings();									// 3. Settings
		else if (currentBtn == 4) s_instructions();								// 4. Instructions
		else if (currentBtn == 5) s_exitFromMenu();								// 5. Exit Game
		pressed = true;
	}
	// If up key, or gamepad up pressed
	else if ((InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) || InputHandler::Instance()->getAxisY(0, 1) < 0) && pressed == false) {
		if (!pressed) setCurrentBtn(BUTTON_UP);
		pressed = true;
		std::cout << "currentButton " << currentBtn << std::endl;
	}
	//else pressed = false;

	// If down key, or gamepad down pressed
	else if ((InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) || InputHandler::Instance()->getAxisY(0, 1) > 0) && pressed == false) {
		if (!pressed) setCurrentBtn(BUTTON_DOWN);
		pressed = true;
		std::cout << "currentButton " << currentBtn << std::endl;
	}
	//else pressed = false;

	// 2017/04/22 Leave 1/4 of a second before the button selector moves again
	if (SDL_GetTicks() > btnTimer + 250) {
		btnTimer = SDL_GetTicks();			// Reset time between button presses
		pressed = false;					// Reset ability to press button
	}	

    if(!m_gameObjects.empty()) {										// If the game object list isn't empty
		for(int i = 0; i < m_gameObjects.size(); i++) {
			if(m_gameObjects[i] != 0) {
				m_gameObjects[i]->update();								// Run update function for each object in m_gameObjects list
			}
		}
    }

	selectCurrentButton(m_callbacks);
}

void MainMenuState::render() {										
    if(m_loadingComplete && !m_gameObjects.empty()) {
        for(int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();									// Call draw function for each object in m_gameObjects list
        }
    }
}

/* Add a new callback for each new button */
bool MainMenuState::onEnter() {
	pressed = true;
	btnTimer = 0;

	numButtons = 5;																				// 2017/04/24 There are 5 buttons in the state
	currentBtn = 1;																				// 2017/04/24 Moved currentBtn to MenuState.h
    // parse the state
    StateParser stateParser;																	// Create a new StateParser
    stateParser.parseState("assets/attack.xml", s_menuID, &m_gameObjects, &m_textureIDList);	// Load assets for "MENU" state from XML
    
    m_callbacks.push_back(0);
	m_callbacks.push_back(s_menuToPlay);														// Play the game
	m_callbacks.push_back(s_highScores);														// Go to high scores	
	m_callbacks.push_back(s_settings);															// Go to settings	
	m_callbacks.push_back(s_instructions);														// Go to instructions	
    m_callbacks.push_back(s_exitFromMenu);														// Exit the game
        
    setCallbacks(m_callbacks);																	// set the callbacks for menu items
    
    m_loadingComplete = true;
    std::cout << "entering MenuState\n";

	selectCurrentButton(m_callbacks);

    return true;
}

bool MainMenuState::onExit() {
    m_exiting = true;											// Set exiting the menu to true
    
    // clean the game objects
    if(m_loadingComplete && !m_gameObjects.empty()) {
		m_gameObjects.back()->clean();							// Call clean function
		m_gameObjects.pop_back();
    }

	m_textureIDList.clear();									// Clear the texture list
	m_gameObjects.clear();										// Clear the m_gameObjects list
	    
    /* clear the texture manager
    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
	*/
        
    TheInputHandler::Instance()->reset();						// reset the input handler
    
    std::cout << "exiting MenuState\n";

    return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks) {
    if(!m_gameObjects.empty()) {													// If its not empty
        for(int i = 0; i < m_gameObjects.size(); i++) {								// Go through the game objects list
            if(dynamic_cast<MenuButton*>(m_gameObjects[i])) {						// if they are of type MenuButton then assign a callback based on the id passed in from the file
                MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
                pButton->setCallback(callbacks[pButton->getCallbackID()]);
            }
        }
    }
}

// Original version of function -> Tidied up elsewhere
void MainMenuState::selectCurrentButton(const std::vector<Callback>& callbacks) {
	if (!m_gameObjects.empty()) {													// If its not empty
		for (int i = 0; i < m_gameObjects.size(); i++) {							// Go through the game objects list
			if (dynamic_cast<MenuButton*>(m_gameObjects[i])) {						// if they are of type MenuButton then assign a callback based on the id passed in from the file
				MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
				//pButton->setCallback(callbacks[pButton->getCallbackID()]);
				//std::cout << "Button callback " << pButton->getCallbackID() << " frame " << pButton->getCurrentFrame() << std::endl; // print the callbacks
				//pButton->setCurrentFrame(1); // MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2

				if (pButton->getCallbackID() == currentBtn) {
					//pButton->testcase();
					pButton->selected = true;
					//pButton->m_bReleased = false;	// not released = selected
				}
				else pButton->selected = false;

				//std::cout << "Button callback " << pButton->getCallbackID() << " frame " << pButton->getCurrentFrame() << std::endl; // print the callbacks

			}
		}
	}
}
