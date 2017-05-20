/*
    MenuState.h
    SDL Game Programming Book
  
    Created by shaun mitchell on 09/02/2013.
    Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/03/16	Added call back for Settings button to enter Settings Menu state from Main Menu state
		2017/02/03	Added call back for High Scores button to enter High Scores state from Main Menu state	
*/

#ifndef __SDL_Game_Programming_Book__MenuState__
#define __SDL_Game_Programming_Book__MenuState__

#include <vector>
#include "MenuState.h"
#include "GameObject.h"

class MainMenuState : public MenuState {
public:
    virtual ~MainMenuState() {}

    virtual void update();
    virtual void render();
    
    virtual bool onEnter(); 
    virtual bool onExit(); 
    
    virtual std::string getStateID() const { return s_menuID; }
    
private:
	void selectCurrentButton(const std::vector<Callback>& callbacks);	// 2017/04/22 test

    virtual void setCallbacks(const std::vector<Callback>& callbacks);
    
    // call back functions for menu items
    static void s_menuToPlay();
	static void s_highScores();			// 2017/02/03 Added high scores call back
	static void s_settings();			// 2017/03/16 Added settings call back
    static void s_exitFromMenu();
    
    static const std::string s_menuID;
    
    std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__SDL_Game_Programming_Book__MenuState__) */
