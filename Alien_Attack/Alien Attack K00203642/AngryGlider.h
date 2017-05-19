/*
	AngryGlider.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/03/14	Added Angry Glider enemy based on the Glider enemy
*/

#ifndef ANGRY_GLIDER_H
#define ANGRY_GLIDER_H

#include "AngryGlider.h"

class AngryGlider : public Glider {
public:

	virtual ~AngryGlider() {}

	AngryGlider() : Glider() {
		m_bulletFiringSpeed = 25;
		m_moveSpeed = 3;
	}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams) {
		ShooterObject::load(std::move(pParams));

		m_velocity.setX(-m_moveSpeed);
	}

	virtual void update() {
		if (!m_bDying) {
			if (m_bulletCounter == m_bulletFiringSpeed) {
				TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 15, 16, 16, "bullet4", 1, Vector2D(-10, 0));
				m_bulletCounter = 0;
			}

			m_bulletCounter++;
		}
		else {
			m_velocity.setX(0);
			doDyingAnimation();
		}

		ShooterObject::update();
	}
};

class AngryGliderCreator : public BaseCreator {
	GameObject* createGameObject() const {
		return new AngryGlider();
	}
};


#endif
