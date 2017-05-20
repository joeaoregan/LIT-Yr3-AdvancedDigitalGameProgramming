/*	
	Pounder.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/23	Added Pounder enemy based, object moves down from top of screen acting as a moving obstacle
*/

#ifndef POUNDER_H
#define POUNDER_H

#include "Enemy.h"
#include "GameObjectFactory.h"	// BaseCreator

bool pFalling = true;

class Pounder : public Enemy {
public:
	virtual ~Pounder() {}

	Pounder() : Enemy() {
		//m_dyingTime = 50;
		m_health = 3;
		m_moveSpeed = 2;				// 2017/04/23 divides into 128 a bit more evenly than 3
		//m_bulletFiringSpeed = 50;
	}

	virtual void collision() {
		//m_health -= 1;
	}
	
	virtual void update() {
		if (!m_bDying) {
			scroll(Game::Instance()->getScrollSpeed());

			if (m_position.getY() == 224) pFalling = true;
			else if (m_position.getY() == 352) pFalling = false;

			if (pFalling) m_velocity.setY(m_moveSpeed);
			else m_velocity.setY(-8);
		}
		
		ShooterObject::update();
	}

	virtual void draw() {
		ShooterObject::draw();					// 2017/04/22 Draw inherited from shooterObject
	}
};

class PounderCreator : public BaseCreator {
	GameObject* createGameObject() const {
		return new Pounder();
	}
};

#endif