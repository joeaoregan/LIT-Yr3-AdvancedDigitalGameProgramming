/*
	PowerUp.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/23	Added Power Up class, with texture and sound fx
*/

#ifndef POWERUP_H
#define POWERUP_H

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class PowerUp : public ShooterObject {
public:
	PowerUp() {
		setName("Power Up");
		setTextureID("powerUpID");
		m_bDead = false;	//2017/04/16 Set object alive
		m_moveSpeed = 1; 
		m_bDying = false;
	}

	virtual ~PowerUp() {}
	
	virtual void load(std::unique_ptr<LoaderParams> const &pParams) {
		ShooterObject::load(std::move(pParams));

		m_velocity.setX(-m_moveSpeed);
	}

	//virtual void draw() {};

	virtual void update() {
		if (!m_bDying) {
			scroll(TheGame::Instance()->getScrollSpeed());		// 2017/04/22 Scroll moves with background
		}		
	}

	//virtual void clean() {};
	virtual void collision() {
		kill();													// Kill the Power Up
		SoundManager::Instance()->playSound("puFX", 0);			// Player Sound FX for Power Up
	};

	virtual std::string type() { return "PowerUp"; }			// Set the type
};

class PowerUpCreator : public BaseCreator {
	GameObject* createGameObject() const {
		return new PowerUp();
	}
};

#endif
