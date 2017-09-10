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

#include "GameState.h"

enum buttonMove {BUTTON_UP, BUTTON_DOWN};	// Enum to make gamepad / keyboard button selection more readable

class MenuState : public GameState {
public:    
    virtual ~MenuState() {}
	
	void setCurrentBtn(int a) {
		if (a == BUTTON_UP) currentBtn--;
		else if (a == BUTTON_DOWN) currentBtn++;

		if (currentBtn > numButtons) currentBtn = 1;
		if (currentBtn < 1) currentBtn = numButtons;
	}
    
protected:    
    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
    
    std::vector<Callback> m_callbacks;

	unsigned int btnTimer = 0;	// 2017/04/24 Delay between buttons. Moved from MainMenuState to be used by all menus
	bool pressed = false;

	int currentBtn;			// Current selected menu button for keyboard / gamepad // 2017/04/24 Moved from Main Menu State
	int numButtons;			// The number of buttons in the menu/state
};


#endif
