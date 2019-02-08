/*
	
	AngryGlider.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/03/14	Added Angry Glider enemy based on the Glider enemy
*/

#ifndef ANGRY_GLIDER_H
#define ANGRY_GLIDER_H

#include "Glider.h"

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
				BulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 15, 16, 16, "bullet4", 1, Vector2D(-10, 0));
				m_bulletCounter = 0;
			}

			m_bulletCounter++;

			if (m_position.getX() > Game::Instance()->playerX) {
				if (m_position.getY() - Game::Instance()->playerY >= 0) {				// Below player
					if (m_position.getY() - Game::Instance()->playerY >= m_moveSpeed)
						m_velocity.setY(-m_moveSpeed);									// Move up. No need to make smaller movements at the moment, as velocity is v.low anyway. Movement is jerky without this check
				}
				if (m_position.getY() - Game::Instance()->playerY < getHeight()) {		// Above player
					m_velocity.setY(m_moveSpeed);										// Move Down
				}
			}
			//if (Game::Instance()->playerY < m_position.getY()) m_velocity.setY(m_moveSpeed);
			//else if (Game::Instance()->playerY < m_position.getY()) m_velocity.setY(-m_moveSpeed);
			//else if (Game::Instance()->playerY == m_position.getY()) m_velocity.setY(0);
		}
		else {
			Game::Instance()->setScore(Game::Instance()->getScore() + m_score);
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
