/*
	EnterNameState.cpp
  
	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/22	Created state for entering name, as entering text has a lot of overhead, and text requires a number of button presses for each character
*/


//#include <iostream>
//#include "EnterNameState.h"

#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"
/*
const std::string EnterNameState::s_nameID = "ENTERNAME";						// Enter Name State ID

void EnterNameState::s_nameToGame() {
	Game::Instance()->getStateMachine()->popState();							// Remove the current Enter Name state
	Game::Instance()->getStateMachine()->changeState(new PlayState());			// Add the Play State and start the game
}

void EnterNameState::s_returnToMenu() {
	Game::Instance()->getStateMachine()->popState();							// Remove the current Enter Name state
	Game::Instance()->getStateMachine()->changeState(new MainMenuState());		// Add the Main Menu state
}

bool nameEntered = false;
std::string inputText = "Name";
bool quit = false;
unsigned int readyTextTimer;
bool renderText;
SDL_Event event;

void EnterNameState::update() {
	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->update();
		}

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
			Game::Instance()->getStateMachine()->pushState(new MainMenuState());// Return to main menu when Esc key is pressed
		}
	}

	// 2017/04/22 Pressing the B button returns to game
	if (InputHandler::Instance()->getButtonState(0, 1)) {						// 2017/04/22	Uncommented. Button 1 is B on NVidia controller
		s_returnToMenu();														// Return to the main menu when B is pressed
		std::cout << "Back Pressed" << std::endl;
	}

	while (SDL_PollEvent(&event) != 0) {
		//User requests quit
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		//Special key input
		else if (event.type == SDL_KEYDOWN) {
			//Handle backspace
			if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {		// backspace -> remove the last character from the string
				//lop off character
				inputText.pop_back();
				renderText = true;		// Set the text update flag
			}
			//Handle copy
			else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {	// Ctrl + c -> copy the text to the clip board
				SDL_SetClipboardText(inputText.c_str());
			}
			//Handle paste
			else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {	// Ctrl + v -> get the text from the clipboard
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
}

void EnterNameState::render() {
	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->draw();
		}
	}

	// CHANGE THIS TO RETURN TO MENU TEXT 
	Texture::Instance()->draw("return", 130, 450, 340, 20, Game::Instance()->getRenderer());	// 2017/04/22 Indicate to player that B button returns to game play
}

bool EnterNameState::onEnter() {
	Texture::Instance()->loadEnterNameText("Please Enter Your Name:", Game::Instance()->getRenderer());

	StateParser stateParser;
	stateParser.parseState("assets/attack.xml", s_nameID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_returnToMenu);			// 1. Return to the menu 
	m_callbacks.push_back(s_nameToGame);			// 2. Play the game

	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "Entering Enter Name State\n";
	return true;
}

bool EnterNameState::onExit() {
	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->clean();
			delete m_gameObjects[i];
		}
		m_gameObjects.clear();
	}

	// clear the texture manager
	for (int i = 0; i < m_textureIDList.size(); i++) {
		Texture::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	InputHandler::Instance()->reset();

	std::cout << "Exiting Enter Name State\n";

	return true;
}

void EnterNameState::setCallbacks(const std::vector<Callback>& callbacks) {
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

*/