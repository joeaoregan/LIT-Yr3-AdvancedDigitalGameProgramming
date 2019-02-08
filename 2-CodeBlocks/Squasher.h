/*
	
	Squasher.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/23	Added Squasher enemy based, object moves down from top of screen acting as a moving obstacle
*/

#ifndef SQUASHER_H
#define SQUASHER_H

#include "Enemy.h"
#include "GameObjectFactory.h"	// BaseCreator

bool falling = true;

class Squasher : public Enemy {
public:
	virtual ~Squasher() {}

	Squasher() : Enemy() {
		//m_dyingTime = 50;
		m_health = 3;
		m_moveSpeed = 8;				// 2017/04/23 divides into 128 a bit more evenly than 3
		//m_bulletFiringSpeed = 50;
	}

	virtual void collision() {
		//m_health -= 1;
	}
	
	virtual void update() {
		if (!m_bDying) {
			scroll(Game::Instance()->getScrollSpeed());

			//if (m_position.getY() < 92 && m_position.getY() >= -30)
			//if (m_position.getY() < 96)	m_velocity.setY(m_moveSpeed);	// Adjust movement for Y up to 96

			if (m_position.getY() == 96) {
				falling = false;
				SoundManager::Instance()->playSound("blastFX", 0);			// Play blast effect, indicating collision
			}
			else if (m_position.getY() == -32) falling = true;

			if (falling) m_velocity.setY(m_moveSpeed);
			else m_velocity.setY(-2);


			//else (m_velocity.setY(-2));
		}
		
		ShooterObject::update();
	}

	virtual void draw() {
		ShooterObject::draw();					// 2017/04/22 Draw inherited from shooterObject
	}
};

class SquasherCreator : public BaseCreator {
	GameObject* createGameObject() const {
		return new Squasher();
	}
};

#endif