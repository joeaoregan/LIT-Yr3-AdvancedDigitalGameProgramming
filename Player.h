/*
//  Player.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 12/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/22	Added most recent object collided with variable to adjust collision functionality for health, and health bar
*/

#ifndef __SDL_Game_Programming_Book__Player__
#define __SDL_Game_Programming_Book__Player__

enum collideTypes { BULLET };

#include <iostream>
#include <vector>
#include "ShooterObject.h"
#include "GameObjectFactory.h"

//#include "StatusBar.h"		// 2017/04/22 Draw a status bar for the player

class Player : public ShooterObject {
public:    
    Player();
    virtual ~Player() {}
    
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    
    virtual void draw();
    virtual void update();
    virtual void clean();
    
    virtual void collision();
    
    virtual std::string type() { return "Player"; }

	// 2017/04/22 Set the most recent collision for the player, to apply different collision functionality
	int getRecentCollision() { return recentCollision; };
	void setRecentCollision(int type) { recentCollision = type; };

private:

	int recentCollision;						// 2017/04/22 Store the most recent collision

	//StatusBar barPl;							// 2017/04/22 Add health bar for player

	void fireBullet(int type, int &counter);	// 2017/04/22 Added fireBullet function to remove repeat code for firing Player weapons
        
    void ressurect();			// bring the player back if there are lives left    

    void handleInput();			// handle any input from the keyboard, mouse, or joystick
    
    void handleAnimation();		// handle any animation for the player

    // player can be invulnerable for a time
    int m_invulnerable;
    int m_invulnerableTime;
    int m_invulnerableCounter;
};

// for the factory
class PlayerCreator : public BaseCreator {
    GameObject* createGameObject() const     {
        return new Player();
    }
};

#endif /* defined(__SDL_Game_Programming_Book__Player__) */
