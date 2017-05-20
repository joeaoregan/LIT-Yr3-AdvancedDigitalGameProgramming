/*
	SettingsState.cpp

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/23	Pressing Backspace also returns to Main Menu
		2017/04/22	Pressing Esc or B button on gamepad, returns to Main Menu
		2017/03/23	Pressing F11 or the Full Screen button in the settings menu Toggles between Full Screen and Windowed view of the game
		2017/03/16	The music button in the Settings Menu turns the music On / Off
					Added Settings menu with buttons for altering game settings
*/

#include <iostream>
#include "SettingsState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "SoundManager.h"	// 2017/03/16 Include Sound Manager so music can be turned on / off

const std::string SettingsState::s_SettingsID = "SETTINGS";

// Callbacks
void SettingsState::s_settingsToMain() {
	Game::Instance()->getStateMachine()->changeState(new MainMenuState()); /* Return to main menu from settings */
}

void SettingsState::s_musicOnOff() {
	SoundManager::Instance()->pausePlayMusic();			/* 2017/03/16 Turn the music on / off */
}

void SettingsState::s_volumeUp() {
	//SoundManager::Instance()->();
	std::cout << "volume up" << std::endl;				/* 2017/04/25 Turn the audio volume up */
}

void SettingsState::s_volumeDown() {
	//SoundManager::Instance()->();
	std::cout << "volume down" << std::endl;			/* 2017/04/25 Turn the audio volume down */
}

void SettingsState::s_fullScreen() {
	/*
		If button F11 is pressed change the game between Full Screen and Windowed
		This option can also be selected from the settings menu of the game
	*/
		Game::Instance()->fullScreenOrWindowed();		/* 2017/03/16 Turn full screen on / off */
}

void SettingsState::update() {
	// Handle button presses
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN) || InputHandler::Instance()->getButtonState(0, 0)) {
		if (currentBtn == 1) s_musicOnOff();								// 1. Turn Music on or off
		else if (currentBtn == 2) s_fullScreen();							// 2. Make the game full screen
		else if (currentBtn == 3) s_volumeDown();							// 3. Volume down
		else if (currentBtn == 4) s_volumeUp();								// 4. Volume up
		else if (currentBtn == 5) s_settingsToMain();						// 5. Return to main menu
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE) ||	// Press Esc key to
		InputHandler::Instance()->isKeyDown(SDL_SCANCODE_BACKSPACE) ||		// 2017/04/23 or backspace
		InputHandler::Instance()->getButtonState(0, 1)) {					// 2017/04/22 OR Gamepad button B
		s_settingsToMain();													// Return to Main Menu
	}

	// If up key, or gamepad up pressed
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) || InputHandler::Instance()->getAxisY(0, 1) < 0) {
		if (!pressed) setCurrentBtn(BUTTON_UP);
		pressed = true;
		std::cout << "currentButton " << currentBtn << std::endl;
	}
	//else pressed = false;

	// If down key, or gamepad down pressed
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) || InputHandler::Instance()->getAxisY(0, 1) > 0) {
		if (!pressed) setCurrentBtn(BUTTON_DOWN);
		pressed = true;
		std::cout << "currentButton " << currentBtn << std::endl;
	}

	selectCurrentButton();

	// 2017/04/22 Leave 1/4 of a second before the button selector moves again
	if (SDL_GetTicks() > btnTimer + 250) {
		btnTimer = SDL_GetTicks();			// Reset time between button presses
		pressed = false;					// Reset ability to press button
	}

	//else pressed = false;
	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->update();
		}
	}
}

void SettingsState::render() {
	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->draw();
		}
	}
}

bool SettingsState::onEnter() {
	numButtons = 5;								// 2017/04/24 There are 2 buttons in the state
	currentBtn = 1;								// Set the current button

	StateParser stateParser;
	stateParser.parseState("assets/attack.xml", s_SettingsID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_fullScreen);		// CallbackID = 1	Make the game Full Screen or windowed
	m_callbacks.push_back(s_musicOnOff);		// CallbackID = 2	Turn the music on or off
	m_callbacks.push_back(s_volumeDown);		// CallbackID = 3	Volume Down
	m_callbacks.push_back(s_volumeUp);			// CallbackID = 4	Volume Up
	m_callbacks.push_back(s_settingsToMain);	// CallbackID = 5	Return to main menu

	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	selectCurrentButton();
	std::cout << "Entering Settings State\n";
	return true;
}

bool SettingsState::onExit() {
	m_exiting = true;

	TheInputHandler::Instance()->reset();

	std::cout << "Exiting Settings State\n";

	return true;
}

void SettingsState::setCallbacks(const std::vector<Callback>& callbacks) {
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

void SettingsState::selectCurrentButton() {
	if (!m_gameObjects.empty()) {													// If its not empty
		for (int i = 0; i < m_gameObjects.size(); i++) {							// Go through the game objects list
			if (dynamic_cast<MenuButton*>(m_gameObjects[i])) {						// if they are of type MenuButton then assign a callback based on the id passed in from the file
				MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);

				if (pButton->getCallbackID() == currentBtn) pButton->selected = true;
				else pButton->selected = false;
			}
		}
	}
}

