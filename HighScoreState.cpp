/*
	2017/02/03
	HighScoreState.cpp.
*/

#include <iostream>
#include "HighScoreState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string HighScoreState::s_HighScoreID = "HIGHSCORES";

void HighScoreState::s_highscoresToMain() {
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void HighScoreState::update() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {				// Press escape to return to main menu
		TheGame::Instance()->getStateMachine()->pushState(new MainMenuState());
	}

	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->update();
		}
	}
}

void HighScoreState::render() {
	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->draw();
		}
	}

	TheTextureManager::Instance()->drawFrame("scoreTitle", (SCREEN_WIDTH - 410 ) / 2, 20, 410, 64, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
	
	TheTextureManager::Instance()->drawText("highScoresID", 65, 100, TheGame::Instance()->getRenderer());

	// Put high score screen output in here
	//std::cout << "Rendering HighScoreState\n";			// will loop over and over
}

bool HighScoreState::onEnter() {
	TheTextureManager::Instance()->load("assets/TitleHighScores.png", "scoreTitle", TheGame::Instance()->getRenderer()); 
	
	TheTextureManager::Instance()->loadHighScoresText(TheGame::Instance()->getRenderer());
	//TheTextureManager::Instance()->drawText("highScoresID", 150, 100, TheGame::Instance()->getRenderer());
	
	StateParser stateParser;
	stateParser.parseState("assets/attack.xml", s_HighScoreID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_highscoresToMain);

	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "entering HighScoreState\n";
	return true;
}

bool HighScoreState::onExit() {
	m_exiting = true;

	TheInputHandler::Instance()->reset();

	std::cout << "exiting HighScoreState\n";
	return true;
}

void HighScoreState::setCallbacks(const std::vector<Callback>& callbacks) {
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

