/*
//  Turret.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 29/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by : Joe O'Regan
	Student Number : K00203642

	Done :
		2017/04/22	Added Healthbar for Turret
*/

#ifndef __SDL_Game_Programming_Book__Turret__
#define __SDL_Game_Programming_Book__Turret__

#include <iostream>
#include "GameObjectFactory.h"
#include "BulletHandler.h"
#include "SoundManager.h"
#include <math.h>
#include "Enemy.h"
//#include "StatusBar.h"	// 2017/04/22

class Turret : public Enemy
{
public:
    
    Turret() {
        m_dyingTime = 1000;
		//m_health = 15;
		m_health = TURRET_HEALTH;
        m_bulletFiringSpeed = 50;
    }
    
    virtual ~Turret() {}

    virtual void collision() {
        m_health -= 1;
        
        if(m_health == 0) {
            if(!m_bPlayedDeathSound) {
                TheSoundManager::Instance()->playSound("explode", 0);
                
                m_textureID = "largeexplosion";
                m_currentFrame = 0;
                m_numFrames = 9;
                m_width = 60;
                m_height = 60;
                m_bDying = true;
            }            
        }
    }
    
    virtual void update() {
        if(!m_bDying) {
            // we want to scroll this object with the rest
            scroll(TheGame::Instance()->getScrollSpeed());
            
            if(m_bulletCounter == m_bulletFiringSpeed) {
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet2", 1, Vector2D(-3, -3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(0, -3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(3, -3));
                m_bulletCounter = 0;
            }
            
            m_bulletCounter++;
        }
        else {
            scroll(TheGame::Instance()->getScrollSpeed());
            doDyingAnimation();
        }
        
    }

	//StatusBar barTu;	// 2017/04/22 Draw a health bar for the turret
	// 2017/04/22 Added draw function
	virtual void draw() {
		ShooterObject::draw();					// 2017/04/22

		// Health Bar
		if (!m_bDying) bar.turretHealthBar(m_position.getX() - 20, m_position.getY() + 75, 100, m_health); // 2017/04/22 If the Turret is not dying draw the health bar
	}
};

class TurretCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Turret();
    }
};


#endif /* defined(__SDL_Game_Programming_Book__Turret__) */
