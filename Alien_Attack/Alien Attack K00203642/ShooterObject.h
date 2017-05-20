/*
//  SDLGameObject.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 19/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/21
*/

#ifndef __SDL_Game_Programming_Book__SDLGameObject__
#define __SDL_Game_Programming_Book__SDLGameObject__

#include <SDL.h>
#include "GameObject.h"

class ShooterObject : public GameObject {
public:    
    virtual ~ShooterObject() {}

    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    
    virtual void draw();
    virtual void update();
    
    virtual void clean() {}
    virtual void collision() {}
    
    virtual std::string type() { return "SDLGameObject"; }
    
protected:    
    ShooterObject();
    
    void doDyingAnimation();
    
    int m_bulletFiringSpeed;
    int m_bulletCounter;
	int m_bullet2Counter;	// 2017/04/21 Counter for CTRL button weapon
	int m_bullet3Counter;	// 2017/04/21 Counter for Gamepad bullet 1
	int m_bullet4Counter;	// 2017/04/22 Counter for Gamepad bullet 2 (bullet2Counter on keyboard)
    int m_moveSpeed;
    
    // how long the death animation takes, along with a counter
    int m_dyingTime;
    int m_dyingCounter;
    
    // has the explosion sound played?
    bool m_bPlayedDeathSound;
};

#endif /* defined(__SDL_Game_Programming_Book__SDLGameObject__) */
