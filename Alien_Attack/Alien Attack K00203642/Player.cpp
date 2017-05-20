/*
	Player.cpp
	SDL Game Programming Book

	Created by shaun mitchell on 12/01/2013.
	Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/22	Added most recent object collided with variable to adjust collision functionality for health, and health bar
					Added health bar, health resets when life is lost, and player is resurrected
		2017/03/16	Pressing the M button in game turns Music On / Off
		2017/04/21	Pressing CTRL (right) fires secondary weapon, with own graphic, and sound effect
		2017/04/21	Added secondary weapon for player, requires separate counter for bullets
		2017/04/21	Uncommented and tested Gamepad support for player, requires separate bullet counters or creates multiples
*/

#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "TileLayer.h"
#include "BulletHandler.h"
#include "SoundManager.h"

using namespace std;


Player::Player() :  ShooterObject(),
m_invulnerable(false),
m_invulnerableTime(200),
m_invulnerableCounter(0)
{
}

void Player::collision() {
    // if the player is not invulnerable then set to dying and change values for death animation tile sheet
    if(!m_invulnerable && !TheGame::Instance()->getLevelComplete()) {
		if (getRecentCollision() == BULLET && m_health > 10) {	// if the player recently collided with a bullet and its health is greater than 10
		//if (getRecentCollision() == BULLET) {
			m_health -= 10;											// deduct 10 from health
		}
		else {
			m_textureID = "largeexplosion";
			m_currentFrame = 0;
			m_numFrames = 9;
			m_width = 60;
			m_height = 60;
			m_bDying = true;
		}
    }
}

void Player::load(std::unique_ptr<LoaderParams> const &pParams) {
        ShooterObject::load(std::move(pParams));		// inherited load function
    
    // can set up the players inherited values here

    // set up bullets
    m_bulletFiringSpeed = 13;
    m_moveSpeed = 3;
        
    m_bulletCounter = m_bulletFiringSpeed;	// we want to be able to fire instantly
        
    m_dyingTime = 100;						// time it takes for death explosion
}

void Player::draw() {    
    ShooterObject::draw();					// player has no special drawing requirements

	// Health Bar
	if (!m_bDying) bar.playerHealthBar(m_position.getX(), m_position.getY() + 60, 100, m_health); // 2017/04/22 If the player is not dying draw the health bar
}

void Player::handleAnimation() {
    // if the player is invulnerable we can flash its alpha to let people know
    if(m_invulnerable) {
        // invulnerability is finished, set values back
        if(m_invulnerableCounter == m_invulnerableTime) {
            m_invulnerable = false;
            m_invulnerableCounter = 0;
            m_alpha = 255;
        }
        else // otherwise, flash the alpha on and off
        {
            if(m_alpha == 255) {
                m_alpha = 0;
            }
            else {
                m_alpha = 255;
            }
        }
                
        m_invulnerableCounter++;	// increment our counter
    }
    
    // if the player is not dead then we can change the angle with the velocity to give the impression of a moving helicopter
    if(!m_bDead) {
        if(m_velocity.getX() < 0) {
            m_angle = -10.0;
        }
        else if(m_velocity.getX() > 0) {
            m_angle = 10.0;
        }
        else {
            m_angle = 0.0;
        }
    }
    
    // our standard animation code - for helicopter propellors
    m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}

void Player::update() {
    if(TheGame::Instance()->getLevelComplete()) {
        if(m_position.getX() >= TheGame::Instance()->getGameWidth()) {
            TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
        }
        else {
            m_velocity.setY(0);
            m_velocity.setX(3);
            ShooterObject::update();
            handleAnimation();
        }
    }
    else {
        // if the player is not doing its death animation then update it normally
        if(!m_bDying)  {
            // reset velocity
            m_velocity.setX(0);
            m_velocity.setY(0);
                        
            handleInput();				// get input
                        
            ShooterObject::update();	// do normal position += velocity update
                       
            handleAnimation();			// update the animation
        }
        else // if the player is doing the death animation
        {
            m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
            
            // if the death animation has completed
            if(m_dyingCounter == m_dyingTime) {                
                ressurect();	// ressurect the player
            }
            m_dyingCounter++;
        }
    }
}

void Player::ressurect() {
    TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);
    
    m_position.setX(10);
    m_position.setY(200);
    m_bDying = false;
    
    m_textureID = "player";
    
    m_currentFrame = 0;
    m_numFrames = 5;
    m_width = 101;
    m_height = 46;
    
    m_dyingCounter = 0;
    m_invulnerable = true;

	m_health = 100;	// 2017/04/22 Reset the Players health
}

void Player::clean() {
    ShooterObject::clean();
}

void Player::handleInput() {
	/* 
		If button F11 is pressed change the game between Full Screen and Windowed
		This option can also be selected from the settings menu of the game
	
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F11)) {
		Game::Instance()->fullScreenOrWindowed();
	}
	*/
    if(!m_bDead) {
        // handle keys
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0) {
			m_velocity.setY(-m_moveSpeed);
		}
        else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) && (m_position.getY() + m_height) < TheGame::Instance()->getGameHeight() - 10) {
            m_velocity.setY(m_moveSpeed);
        }
        
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 0) {
            m_velocity.setX(-m_moveSpeed);
        }
        else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && (m_position.getX() + m_width) < TheGame::Instance()->getGameWidth()) {
            m_velocity.setX(m_moveSpeed);
        }
        
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
			fireBullet(1, m_bulletCounter);							// 2017/04/22 Fire bullet function cuts duplicate code
			/*
            if(m_bulletCounter == m_bulletFiringSpeed) {
                TheSoundManager::Instance()->playSound("shoot", 0);
                TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10,0));
                m_bulletCounter = 0;
            }
            
            m_bulletCounter++;	
			*/
        }
        else {
            m_bulletCounter = m_bulletFiringSpeed;
		}

		/*
			New Weapon
			2017-04-21	Pressing CTRL fires a different weapon
						m_bullet2Counter is needed otherwise the bullet fires repeatedly for both CTRL and Space presses
		*/
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RCTRL)) {
			fireBullet(2, m_bullet2Counter);							// 2017/04/22 Fire bullet function cuts duplicate code
			/*
			if (m_bullet2Counter == m_bulletFiringSpeed) {
				SoundManager::Instance()->playSound("fire", 0);																						// Separate sound effect
				BulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet4", 1, Vector2D(10, 0));	// Blue bullet
				m_bullet2Counter = 0;
			}

			m_bullet2Counter++;																														// 2017/04/22 Separate bullet counters are needed
			*/
		}
		else {
			m_bullet2Counter = m_bulletFiringSpeed;
		}		

		/* 2017/03/16 need to change so only happens when not enter name state */
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_M)) {
			SoundManager::Instance()->pausePlayMusic();
		}
        // */
        
        /* 
			handle joysticks 
			2017/04/22	Uncommented - Fires more than 1 bullet at a time
						Added separate bullet counter m_bullet3Counter to allow single bullet to fire at a time
		*/
        if(TheInputHandler::Instance()->joysticksInitialised()) {
			// Fire the first bullet type
			//if (TheInputHandler::Instance()->getButtonState(0, 2)) {
			if (TheInputHandler::Instance()->getButtonState(0, 0)) {		// 2017/04/22 Changed main fire button to X button of gamepad
				fireBullet(1, m_bullet3Counter);							// 2017/04/22 Fire bullet function cuts duplicate code
				/*
                if(m_bullet3Counter == m_bulletFiringSpeed) {
                    TheSoundManager::Instance()->playSound("shoot", 0);
                    TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10,0));
                    m_bullet3Counter = 0;
                }
                
                m_bullet3Counter++;
				*/
            }
            else {
                m_bullet3Counter = m_bulletFiringSpeed;
            }

			// Fire the first bullet type
			if (TheInputHandler::Instance()->getButtonState(0, 1)) {		// 2017/04/22 Added secondary weapon to Y button of gamepad
				fireBullet(2, m_bullet4Counter);							// 2017/04/22 Fire bullet function cuts duplicate code
				/*
				if (m_bullet4Counter == m_bulletFiringSpeed) {
					TheSoundManager::Instance()->playSound("fire", 0);
					TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet4", 1, Vector2D(10, 0));
					m_bullet4Counter = 0;
				}

				m_bullet4Counter++;
				*/
			}
			else {
				m_bullet4Counter = m_bulletFiringSpeed;
			}
			
            
            if((TheInputHandler::Instance()->getAxisX(0, 1) > 0 && (m_position.getX() + m_width) < TheGame::Instance()->getGameWidth()) || (TheInputHandler::Instance()->getAxisX(0, 1) < 0 && m_position.getX() > 0))
            {
                m_velocity.setX(m_moveSpeed * TheInputHandler::Instance()->getAxisX(0, 1));
            }
            
            if((TheInputHandler::Instance()->getAxisY(0, 1) > 0 && (m_position.getY() + m_height) < TheGame::Instance()->getGameHeight() - 10 ) || (TheInputHandler::Instance()->getAxisY(0, 1) < 0 && m_position.getY() > 0))
            {
                m_velocity.setY(m_moveSpeed * TheInputHandler::Instance()->getAxisY(0, 1));
            }
        }
        
    }
}

/*
	2017/04/22	Added bullet firing function to remove repeat code
				Function takes the type of bullet to fire, and a reference to the counter
*/
void Player::fireBullet(int type, int &counter) {
	std::string bulletFXID = "";
	std::string bulletGraphicID = "";

	if (type == 1) {
		bulletFXID = "shoot";
		bulletGraphicID = "bullet1";
	}
	else if (type == 2) {
		bulletFXID = "fire";
		bulletGraphicID = "bullet4";
	}

	if (counter == m_bulletFiringSpeed) {
		TheSoundManager::Instance()->playSound(bulletFXID, 0);
		TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, bulletGraphicID, 1, Vector2D(10, 0));
		counter = 0;
	}

	counter++;
}