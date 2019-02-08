/*
	EnterNameState.cpp
  
	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/22	Created state for entering name, as entering text has a lot of overhead, and text requires a number of button presses for each character
*/

//#include <iostream>
#include "EnterNameState.h"


#include "LevelObjectiveState.h"	// 2017/04/25 Change Enter Name State to move to Level Objective, and then Play State
#include "MainMenuState.h"
#include "PlayState.h"				// 2017/04/25 Enter Name first progressed to Play State
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"

#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

const std::string EnterNameState::s_EnterNameID = "ENTERNAME";					// Enter Name State ID

void EnterNameState::s_enterNameToGame() {
	Game::Instance()->getStateMachine()->changeState(new PlayState());			// Add the Play State and start the game
}

void EnterNameState::s_enterNameToObjective() {
	Game::Instance()->getStateMachine()->changeState(new LevelObjectiveState());// Switch to the Level Objective instead of Play State
}

void EnterNameState::s_enterNameToMain() {
	Game::Instance()->getStateMachine()->changeState(new MainMenuState());		// Add the Main Menu state
}

//bool nameEntered1 = false;
std::string inputText1 = "Player";												// Players name, default "Player"
bool renderText1;
SDL_Event event1;

void EnterNameState::update() {
	if (m_loadingComplete && !m_gameObjects.empty()) {									// If media was loaded and the game object list is not empty
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->update();													// update the game objects
		}
	}

	// 2017/04/22 Pressing the B button returns to game
	// Input Handler set to not work for entering text
	//if (InputHandler::Instance()->getButtonState(0, 1)) {								// 2017/04/22	Uncommented. Button 1 is B on NVidia controller
	//	s_enterNameToMain();															// 2017/04/22	Return to the main menu when B is pressed
	//	std::cout << "Back Pressed" << std::endl;
	//}

	while (SDL_PollEvent(&event1) != 0) {		
		if (event1.type == SDL_JOYBUTTONDOWN) {
			if (event1.jbutton.button == 0) {
				Game::Instance()->setPlayerName(inputText1);							// 2017/04/22	Set The Players name
				//s_enterNameToGame();													// 2017/04/22	Advance to Game when A is pressed on controller
				s_enterNameToObjective();												// 2017/04/25	Advance to Level Objective State instead of Play State
				std::cout << "A Pressed - Play Game" << std::endl;
			}
			else if (event1.jbutton.button == 1) {
				s_enterNameToMain();													// 2017/04/22	Return to the main menu when B is pressed on controller
				std::cout << "B Pressed - Return to Main Menu" << std::endl;
			}
		}										
		// Special key input, backspace, copy and paste
		else if (event1.type == SDL_KEYDOWN) {
			// Handle Esc
			if (event1.key.keysym.sym == SDLK_ESCAPE && inputText1.length() > 0) {		// Esc
				Game::Instance()->getStateMachine()->changeState(new MainMenuState());	// Return to main menu when Esc key is pressed
				std::cout << "Esc pressed" << std::endl;
			}
			// Handle backspace
			if (event1.key.keysym.sym == SDLK_BACKSPACE && inputText1.length() > 0) {	// backspace -> remove the last character from the string
				inputText1.pop_back();													// lop off character
				renderText1 = true;														// Set the text update flag
			}
			// Handle copy
			else if (event1.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {// Ctrl + c -> copy the text to the clip board
				SDL_SetClipboardText(inputText1.c_str());
			}
			// Handle paste
			else if (event1.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {// Ctrl + v -> get the text from the clipboard
				inputText1 = SDL_GetClipboardText();
				renderText1 = true;														// Set the text update flag
			}
			// Handle Enter
			else if (event1.key.keysym.sym == SDLK_RETURN) {
				Game::Instance()->setPlayerName(inputText1);							// 2017/04/22 Set the Players name for high scores
				//s_enterNameToGame();													// 2017/04/22 Start the game
				s_enterNameToObjective();												// 2017/04/25	Advance to Level Objective State instead of Play State
			}
		}
		//Special text input event
		else if (event1.type == SDL_TEXTINPUT) {
			if (!((event1.text.text[0] == 'c' || event1.text.text[0] == 'C') &&			// If not copying
				(event1.text.text[0] == 'v' || event1.text.text[0] == 'V') &&			// or pasting
				SDL_GetModState() & KMOD_CTRL)) {
				if (inputText1.length() < 12)											// 2017/04/24 Limit the charcters entered to 12
					inputText1 += event1.text.text;										// Append character
				renderText1 = true;														// Set text has been entered
			}
		}

		if (renderText1) {																// If text entered, render it			
			if (inputText1 != "") Texture::Instance()->loadInputText(inputText1);		// If the input text is not empty, render new text	
			else Texture::Instance()->loadInputText(" ");								// If text is empty, put a space. Has to be something in the string to render it
		}

		renderText1 = false;															// Reset text entry
	}
}

void EnterNameState::render() {	
	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->draw();
		}
	}

	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x00, 0x00, 0x00, 0xFF);					// Clear background
	Texture::Instance()->draw("enterNameID", 200, 100, 400, 20, Game::Instance()->getRenderer());		// Display enter name message
	Texture::Instance()->loadInputText(inputText1);														// Render the input text to a texture
	Texture::Instance()->drawText("inputTextID", 200, 150, Game::Instance()->getRenderer());			// Display the input text on screen
	/*
	if (renderText1) {																	// Rerender text if needed			
		if (inputText1 != "") {															// If the input text is not empty				
			//gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColor);
			Texture::Instance()->loadInputText(inputText1);								// Render new text
		}
		//Text is empty
		else {
			//Render space texture
			//gInputTextTexture.loadFromRenderedText(" ", textColor);					// Can't render an empty string, so has to be space
			Texture::Instance()->loadInputText(" ");									// Has to be something in the string to render it
		}
	}

	renderText1 = false;																				// flag that keeps track of whether we need to update the texture
	*/
	// CHANGE THIS TO RETURN TO MENU TEXT 
	//Texture::Instance()->draw("return", 230, 450, 340, 20, Game::Instance()->getRenderer());			// 2017/04/22 Indicate to player that B button returns to game play
	Texture::Instance()->draw("returnToMenuID", 215, 475, 370, 100, Game::Instance()->getRenderer());	// 2017/04/22 Indicate to player that B button returns to game play	
																										
	//std::cout << "Enter Name Render()" << std::endl;	
}

bool EnterNameState::onEnter() {
	Game::Instance()->setEnterTextState(true);											// 2017/04/22 Allow text to be entered

	//Game::Instance()->setPlayerName("Player");											// 2017/04/22 Set the default Player name to "Player"

	SDL_StartTextInput();

	Texture::Instance()->loadEnterNameText("Please Enter Your Name:");					// Message for Player to enter their name
	
	StateParser stateParser;
	/*
	//stateParser.parseState("assets/attack.xml", s_EnterNameID, &m_gameObjects, &m_textureIDList);	// Not working
	//stateParser.parseState("assets/attack.xml", "ENTERNAME", &m_gameObjects, &m_textureIDList);

	//Texture::Instance()->load("assets/return.png", "return", Game::Instance()->getRenderer());
	*/
	Texture::Instance()->loadReturnToMenuText("To Return To Main Menu\nPress Esc or Backspace\nOn the gamepad press B\nPress Enter to proceed");	// *** NOT DISPLAYING ADDITIONAL LINES resize draw height parameter
	
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_enterNameToMain);			// 1. Return to the menu 
	//m_callbacks.push_back(s_enterNameToGame);			// 2. Play the game
	m_callbacks.push_back(s_enterNameToObjective);		// 2. Proceed to the Level Objective instead of Game state
	
	setCallbacks(m_callbacks);
	
	m_loadingComplete = true;

	renderText1 = true;
	//nameEntered1 = false;	// Input a name

	Texture::Instance()->loadEnterNameText("Please Enter Your Name:");			// Render message indicating to enter name

	std::cout << "Entering Enter Name State\n";
	
	return true;	
}

bool EnterNameState::onExit() {
	Game::Instance()->setEnterTextState(false);									// 2017/04/22 Reset input handling

	if (m_loadingComplete && !m_gameObjects.empty()) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			m_gameObjects[i]->clean();
			delete m_gameObjects[i];
		}
		m_gameObjects.clear();
	}

	// clear the texture manager
	//for (int i = 0; i < m_textureIDList.size(); i++) {
	//	Texture::Instance()->clearFromTextureMap(m_textureIDList[i]);
	//}

	m_textureIDList.clear();

	InputHandler::Instance()->reset();	// Doesn't reset keyboard input
	
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

