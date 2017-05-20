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
#include "StatusBar.h"

StatusBar volBar;			// 2017/04/25 Statusbar for volume
int difficulty;

const std::string SettingsState::s_SettingsID = "SETTINGS";

// Callbacks
void SettingsState::s_settingsToMain() {
	Game::Instance()->getStateMachine()->changeState(new MainMenuState()); /* Return to main menu from settings */
}

void SettingsState::s_musicOnOff() {
	SoundManager::Instance()->pausePlayMusic();			/* 2017/03/16 Turn the music on / off */
}

void SettingsState::s_volumeUpMusic() {
	SoundManager::Instance()->volumeUpMusic();
	std::cout << "volume up" << std::endl;				/* 2017/04/25 Turn the music audio volume up */
}

void SettingsState::s_volumeDownMusic() {
	SoundManager::Instance()->volumeDownMusic();
	std::cout << "volume down" << std::endl;			/* 2017/04/25 Turn the music audio volume down */
}
void SettingsState::s_volumeUpEffects() {
	SoundManager::Instance()->playSound("fire", 0);
	SoundManager::Instance()->volumeUpEffects();
}

void SettingsState::s_volumeDownEffects() {
	SoundManager::Instance()->playSound("fire", 0);
	SoundManager::Instance()->volumeDownEffects();
}
void SettingsState::s_increaseDifficulty() {
	difficulty = Game::Instance()->getDifficulty();
	//difficulty++;
	if (++difficulty > NOT_LIAM) difficulty = NOT_LIAM;
	Game::Instance()->setDifficulty(difficulty);

	std::cout << "Difficulty increased: " << difficulty << std::endl;
}

void SettingsState::s_decreaseDifficulty() {
	difficulty = Game::Instance()->getDifficulty();
	//difficulty--;
	if (--difficulty < LIAM) difficulty = LIAM;
	Game::Instance()->setDifficulty(difficulty);

	std::cout << "Difficulty decreased: " << difficulty << std::endl;
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
		if (currentBtn == 1) s_fullScreen();								// 1. Make the game full screen
		else if (currentBtn == 2) s_musicOnOff();							// 2. Turn Music on or off
		else if (currentBtn == 3) s_volumeDownMusic();						// 3. Music Volume down
		else if (currentBtn == 4) s_volumeUpMusic();						// 4. Music Volume up
		else if (currentBtn == 5) s_volumeDownEffects();					// 5. Effects Volume down
		else if (currentBtn == 6) s_volumeUpEffects();						// 6. Effects Volume up
		else if (currentBtn == 7) s_decreaseDifficulty();					// 7. Decrease the game difficulty
		else if (currentBtn == 8) s_increaseDifficulty();					// 8. Increase the game difficulty (Range is Liam to Hard for difficulty)
		else if (currentBtn == 9) s_settingsToMain();						// 9. Return to main menu
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

	// Volume status bars
	volBar.musicVolumeBar(SoundManager::Instance()->getVolumeMusic());							// 2017/04/25 Draw a status bar for music volume
	Texture::Instance()->draw("volMusic", 300, 250, 200, 50, Game::Instance()->getRenderer());	// Label it
	volBar.effectsVolumeBar(SoundManager::Instance()->getVolumeEffects());						// 2017/04/25 Draw a status bar for effects volume
	Texture::Instance()->draw("volEffects", 300, 300, 200, 50, Game::Instance()->getRenderer());// Label it
	volBar.difficultyBar(Game::Instance()->getDifficulty());									// 2017/04/25 Draw a status bar for the game difficulty
	
	if (Game::Instance()->getDifficulty() == 0) Texture::Instance()->draw("easy", 300, 400, 200, 50, Game::Instance()->getRenderer());			// Label Easy
	else if (Game::Instance()->getDifficulty() == 1) Texture::Instance()->draw("medium", 300, 400, 200, 50, Game::Instance()->getRenderer());	// Label Normal
	else if (Game::Instance()->getDifficulty() == 2) Texture::Instance()->draw("hard", 300, 400, 200, 50, Game::Instance()->getRenderer());		// Label Hard
}

bool SettingsState::onEnter() {	
	numButtons = 9;									// 2017/04/24 There are 2 buttons in the state
	currentBtn = 1;									// Set the current button
	
	StateParser stateParser;
	stateParser.parseState("assets/attack.xml", s_SettingsID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_fullScreen);			// CallbackID = 1	Make the game Full Screen or windowed
	m_callbacks.push_back(s_musicOnOff);			// CallbackID = 2	Turn the music on or off
	m_callbacks.push_back(s_volumeDownMusic);		// CallbackID = 3	Music Volume Down
	m_callbacks.push_back(s_volumeUpMusic);			// CallbackID = 4	Music Volume Up
	m_callbacks.push_back(s_volumeDownEffects);		// CallbackID = 5	Effects Volume Down
	m_callbacks.push_back(s_volumeUpEffects);		// CallbackID = 6	Effects Volume Up
	m_callbacks.push_back(s_decreaseDifficulty);	// CallbackID = 7	Decrease the game difficulty
	m_callbacks.push_back(s_increaseDifficulty);	// CallbackID = 8	Increase the game difficulty (Range is Liam to Hard for difficulty)
	m_callbacks.push_back(s_settingsToMain);		// CallbackID = 9	Return to main menu

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

	pressed = true;
	btnTimer = 0;

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
