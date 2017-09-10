/*
	SettingsState.cpp

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		
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
/* Return to main menu from settings */
void SettingsState::s_settingsToMain() {
	Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}
/* 2017/03/16 Turn the music on / off */
void SettingsState::s_musicOnOff() {
	SoundManager::Instance()->pausePlayMusic();
}
/* 2017/03/16 Turn full screen on / off */
void SettingsState::s_fullScreen() {
	/*
		If button F11 is pressed change the game between Full Screen and Windowed
		This option can also be selected from the settings menu of the game
	*/
		Game::Instance()->fullScreenOrWindowed();
}

void SettingsState::update() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {				// Press escape to return to main menu
		TheGame::Instance()->getStateMachine()->pushState(new MainMenuState());
	}

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

	TheTextureManager::Instance()->drawFrame("settingsTitle", (SCREEN_WIDTH - 280) / 2, 20, 280, 64, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);	// Display title at top of settings menu

	// 2017/03/16 Added buttons for settings
	//Texture::Instance()->drawFrame("musicButton", (SCREEN_WIDTH - 199) / 2, 100, 199, 43, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
	//Texture::Instance()->drawFrame("fullscreenButton", (SCREEN_WIDTH - 163) / 2, 150, 163, 43, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);

	//TheTextureManager::Instance()->drawText("highScoresID", 65, 100, TheGame::Instance()->getRenderer());

	// Put high score screen output in here
	//std::cout << "Rendering HighScoreState\n";			// will loop over and over
}

bool SettingsState::onEnter() {
	TheTextureManager::Instance()->load("assets/TitleSettings.png", "settingsTitle", TheGame::Instance()->getRenderer());	// Load title at top of settings menu
	//TheTextureManager::Instance()->load("assets/buttonMusic.png", "musicButton", TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->load("assets/buttonFullScreen.png", "fullscreenButton", TheGame::Instance()->getRenderer());


	StateParser stateParser;
	stateParser.parseState("assets/attack.xml", s_SettingsID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_settingsToMain);	// CallbackID = 1	Return to main menu
	m_callbacks.push_back(s_musicOnOff);		// CallbackID = 2	Turn the music on or off
	m_callbacks.push_back(s_fullScreen);		// CallbackID = 3	Make the game Full Screen or windowed

	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "entering HighScoreState\n";
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

