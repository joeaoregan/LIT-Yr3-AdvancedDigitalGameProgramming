/*
	InstructionsState.cpp

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/24	Created Instructions State to view game controls
*/

#include <iostream>
#include "InstructionsState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string InstructionsState::s_InstructionID = "INSTRUCTIONS";

void InstructionsState::s_instructionsToMain() {
	Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}

bool displayGamepad = true;

void InstructionsState::update() {
	/*
		If the Esc, Backspace or gamepad B button is pressed, return to main menu
	*/
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE) ||			// If Esc key
		InputHandler::Instance()->isKeyDown(SDL_SCANCODE_BACKSPACE) ||		// 2017/04/23 or backspace
		InputHandler::Instance()->getButtonState(0, 1)) {					// 2017/04/22 OR Gamepad button B
		Game::Instance()->getStateMachine()->pushState(new MainMenuState());// Return to main menu
	}

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) ||			// If left
		InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)	||			// Or right key is pressed
		InputHandler::Instance()->getButtonState(0, 3)) {					// 2017/04/22 If Y button is pressed
		if (!pressed) {
			if (displayGamepad) {
				displayGamepad = false;
			}
			else displayGamepad = true;
		}
		pressed = true;
	}

	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->update();
		}
	}

	// Leave 300ms before selecting next image
	if (SDL_GetTicks() > btnTimer + 300) {
		btnTimer = SDL_GetTicks();
		pressed = false;
	}
}

void InstructionsState::render() {
	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->draw();
		}
	}

	// 2017/04/2016 Switch Image displayed with shoulder button
	if (displayGamepad) Texture::Instance()->drawFrame("controlsG", 10, 100, 780, 386, 0, 0, Game::Instance()->getRenderer(), 0.0, 255);
	else Texture::Instance()->drawFrame("controlsK", 10, 100, 780, 386, 0, 0, Game::Instance()->getRenderer(), 0.0, 255);
}

bool InstructionsState::onEnter() {		
	StateParser stateParser;
	stateParser.parseState("assets/attack.xml", s_InstructionID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_instructionsToMain);

	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "Entering Instructions State\n";
	return true;
}

bool InstructionsState::onExit() {
	m_exiting = true;

	InputHandler::Instance()->reset();

	m_textureIDList.clear();

	std::cout << "Exiting Instructions State\n";
	return true;
}

void InstructionsState::setCallbacks(const std::vector<Callback>& callbacks) {
	// go through the game objects
	if (!m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			// if they are of type MenuButton then assign a callback based on the id passed in from the file
			if (dynamic_cast<MenuButton*>(m_gameObjects[i])) {
				MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
		}
	}
}

