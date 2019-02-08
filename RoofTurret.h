/*
//  RoofTurret.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 30/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by : Joe O'Regan
	Student Number : K00203642

	Done :
		2017/04/22	Added Healthbar for Roof Turret
*/

#ifndef SDL_Game_Programming_Book_RoofTurret_h
#define SDL_Game_Programming_Book_RoofTurret_h

#include "Turret.h"

class RoofTurret : public Turret {
public:
    
    virtual ~RoofTurret() {}
    
    virtual void draw() {
        TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
                                              m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha, SDL_FLIP_VERTICAL);
		
		// Health Bar
		if (!m_bDying) bar.rTurretHealthBar(m_position.getX() - 22, m_position.getY() + 10, 100, m_health); // 2017/04/22 If the Roof Turret is not dying draw the health bar
    }
    
    virtual void update() {
        if(!m_bDying) {
            // we want to scroll this object with the rest
            scroll(TheGame::Instance()->getScrollSpeed());
            
            if(m_bulletCounter == m_bulletFiringSpeed) {
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(-3, 3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(0, 3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(3, 3));
                m_bulletCounter = 0;
            }
            
            m_bulletCounter++;
        }
        else {
            scroll(TheGame::Instance()->getScrollSpeed());
            doDyingAnimation();
        }
    }
};

class RoofTurretCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new RoofTurret();
    }
};

#endif
