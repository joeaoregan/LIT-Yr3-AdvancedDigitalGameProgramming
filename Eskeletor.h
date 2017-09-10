/*
//  Eskeletor.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 30/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/22	Added health bar for Eskeletor, blending with sprite colours
*/

#ifndef SDL_Game_Programming_Book_Escalator_h
#define SDL_Game_Programming_Book_Escalator_h

#include "Enemy.h"

class Eskeletor : public Enemy {
public:    
    virtual ~Eskeletor() {}
    
    Eskeletor() : Enemy() {
        m_dyingTime = 50;
        m_health = 3;
        m_moveSpeed = 3;
        m_bulletFiringSpeed = 50;
    }
    
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
            scroll(TheGame::Instance()->getScrollSpeed());
            m_velocity.setY(m_moveSpeed);
            
            if(m_bulletCounter == m_bulletFiringSpeed) {
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(-3, 0));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(3, 0));
                m_bulletCounter = 0;
            }
            m_bulletCounter++;
            
        }
        else {
            m_velocity.setY(0);
            doDyingAnimation();
        }
        
        ShooterObject::update();
    }

	// 2017/04/22 Added draw function
	virtual void draw() {
		ShooterObject::draw();					// 2017/04/22 Draw inherited from shooterObject
		
		// Health Bar
		if (!m_bDying) bar.eHeManBar(m_position.getX(), m_position.getY(), m_health); // 2017/04/22 If the Turret is not dying draw the health bar
	}
};

class EskeletorCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Eskeletor();
    }
};

#endif