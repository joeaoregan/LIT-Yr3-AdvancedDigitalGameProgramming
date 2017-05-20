/*
//  MenuState.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 26/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/24	Moved setCurrentBtn() function from MainMenuState, and added variables for the current and total buttons
*/

#ifndef SDL_Game_Programming_Book_MenuState_h
#define SDL_Game_Programming_Book_MenuState_h

#include <SDL.h>
#include "GameState.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "SoundManager.h"

static const int TIME_BETWEEN_BUTTON_PRESSES = 200;

enum buttonMove {BUTTON_UP, BUTTON_DOWN};	// Enum to make gamepad / keyboard button selection more readable

class MenuState : public GameState {
public:    
    virtual ~MenuState() {}
	
	void setCurrentBtn(int a) {
		if (a == BUTTON_UP) currentBtn--;			// Highligh button higher up
		else if (a == BUTTON_DOWN) currentBtn++;	// Highlight button lower

		if (currentBtn > numButtons) currentBtn = 1;
		if (currentBtn < 1) currentBtn = numButtons;
	}
	
	// 2017/04/27 Mark button has been pressed
	void setButtonPressed() {
		btnTimer = SDL_GetTicks();					// Set The timer to the current game time
													//pressed = true;							// Set the button pressed to true

		std::cout << "currentButton " << currentBtn << std::endl;
	}

	bool buttonPressed() {
		if (SDL_GetTicks() > btnTimer + TIME_BETWEEN_BUTTON_PRESSES) {			// If time since last button pressed is 1/4 of a second
			btnTimer = SDL_GetTicks();											// Reset time between button presses

			return false;														// OK to accept button press
		}

		return true;															// Not OK to accept button press
	}

	virtual void update() {
		//if (!buttonPressed()) {		
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) ||			// If up key, 
			InputHandler::Instance()->getAxisY(0, 1) < 0) {					// Or gamepad up pressed
			setCurrentBtn(BUTTON_UP);										// Set the current button as up
			SoundManager::Instance()->playSound("buttonFX", 0);				// Play button effect, don't loop
			setButtonPressed();												// Disable ability to press button, and time before button can be pressed again
		}
		else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) ||	// If down key
			InputHandler::Instance()->getAxisY(0, 1) > 0) {					// Or gamepad down pressed
			setCurrentBtn(BUTTON_DOWN);										// Set the current button as down
			SoundManager::Instance()->playSound("buttonFX", 0);				// Play button effect, don't loop
			setButtonPressed();												// Disable ability to press button, and time before button can be pressed again
		}
		//}
	}

protected:    
    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

	virtual void highlightCurrentButton(const std::vector<GameObject *> *pObjects) {
		if (!pObjects->empty()) {															// If list of game objects is not empty
			for (int i = 0; i < pObjects->size(); i++) {									// Go through the game objects list
				if (dynamic_cast<MenuButton*>((*pObjects)[i])) {							// if they are of type MenuButton then assign a callback based on the id passed in from the file
					MenuButton* pButton = dynamic_cast<MenuButton*>((*pObjects)[i]);

					if (pButton->getCallbackID() == currentBtn) {
						pButton->selected = true;
					}
					else {
						pButton->selected = false;
					}
				}
			}
		}
	}
    
    std::vector<Callback> m_callbacks;

	unsigned int btnTimer = 0;							// 2017/04/24 Delay between buttons. Moved from MainMenuState to be used by all menus
	bool pressed = true;

	int currentBtn;										// Current selected menu button for keyboard / gamepad // 2017/04/24 Moved from Main Menu State
	int numButtons;										// The number of buttons in the menu/state
};


#endif
