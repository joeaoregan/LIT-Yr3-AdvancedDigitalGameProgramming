/*
//  CollisionManager.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 28/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/23	Added check for collision between Player and Power Ups
		2017/04/22	Added most recent object collided with variable to adjust collision functionality for health, and health bar
*/

#include "CollisionManager.h"
#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletHandler.h"
#include "TileLayer.h"

void CollisionManager::checkPlayerPowerUpCollision(Player* pPlayer, const std::vector<GameObject*> &objects) {
		SDL_Rect* pRect1 = new SDL_Rect();
		pRect1->x = pPlayer->getPosition().getX();	// Player X coord
		pRect1->y = pPlayer->getPosition().getY();	// Player Y coord
		pRect1->w = pPlayer->getWidth();			// Player width
		pRect1->h = pPlayer->getHeight();			// Player height
		
		//std::cout << "Collisions for Power Ups" << std::endl;

		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->type() != std::string("PowerUp") || !objects[i]->updating()) {	// If the object isn't a power up,
				continue;																	// skip to the next object on the list
			}
			//else std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXX Power Up Found" << std::endl; // test

			SDL_Rect* pRect2 = new SDL_Rect();
			pRect2->x = objects[i]->getPosition().getX();	// Power Up X coord
			pRect2->y = objects[i]->getPosition().getY();	// Power Up Y coord
			pRect2->w = objects[i]->getWidth();				// Power Up Width
			pRect2->h = objects[i]->getHeight();			// Power Up Height

			if (RectRect(pRect1, pRect2)) {
				if (!objects[i]->dead() && !objects[i]->dying()) {
					pPlayer->setRecentCollision(POWERUP);	// 2017/04/23 Set the most recent object collided with to Power Up to perform relevant collision functionality

					pPlayer->collision();					// Handle Player collisions
					std::cout << "Player collision with Power Up" << std::endl;

					//objects[i]->kill();					// Kill the power up object
					objects[i]->collision();				// Handle collision for power up
				}
			}
			delete pRect2;									// Clear the rectangle (box collider)
		}

		delete pRect1;										// Clear the rectangle
	}

void CollisionManager::checkPlayerEnemyBulletCollision(Player* pPlayer) {
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pPlayer->getPosition().getX();	// Get Players x coord
    pRect1->y = pPlayer->getPosition().getY();	// Get Players y coord
    pRect1->w = pPlayer->getWidth();			// Get Players width
    pRect1->h = pPlayer->getHeight();			// Get Players height
    
    for(int i = 0; i < BulletHandler::Instance()->getEnemyBullets().size(); i++) {
        EnemyBullet* pEnemyBullet = BulletHandler::Instance()->getEnemyBullets()[i];
        
        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = pEnemyBullet->getPosition().getX();	// Bullet x coord
        pRect2->y = pEnemyBullet->getPosition().getY();	// Bullet y coord
        
        pRect2->w = pEnemyBullet->getWidth();			// Bullet width
        pRect2->h = pEnemyBullet->getHeight();			// Bullet height
        
        if(RectRect(pRect1, pRect2)) {
            if(!pPlayer->dying() && !pEnemyBullet->dying()) {
                pEnemyBullet->collision();

				pPlayer->setRecentCollision(BULLET);	// 2017/04/22 Set the most recent object collided with to bullet to perform relevant collision functionality

                pPlayer->collision();					// Change this function to adjust health
            }
        }
        
        delete pRect2;	// Clear the rectangle
    }
    
    delete pRect1;		// Clear the rectangle
}

void CollisionManager::checkEnemyPlayerBulletCollision(const std::vector<GameObject *> &objects) {
    for(int i = 0; i < objects.size(); i++) {
        GameObject* pObject = objects[i];
        
        for(int j = 0; j < TheBulletHandler::Instance()->getPlayerBullets().size(); j++) {
            if(pObject->type() != std::string("Enemy") || !pObject->updating()) {
                continue;
            }
            
            SDL_Rect* pRect1 = new SDL_Rect();
            pRect1->x = pObject->getPosition().getX();
            pRect1->y = pObject->getPosition().getY();
            pRect1->w = pObject->getWidth();
            pRect1->h = pObject->getHeight();
            
            PlayerBullet* pPlayerBullet = TheBulletHandler::Instance()->getPlayerBullets()[j];
            
            SDL_Rect* pRect2 = new SDL_Rect();
            pRect2->x = pPlayerBullet->getPosition().getX();
            pRect2->y = pPlayerBullet->getPosition().getY();
            pRect2->w = pPlayerBullet->getWidth();
            pRect2->h = pPlayerBullet->getHeight();
            
            if(RectRect(pRect1, pRect2)) {
                if(!pObject->dying() && !pPlayerBullet->dying()) {
                    pPlayerBullet->collision();
                    pObject->collision();
                }                
            }
            
            delete pRect1;
            delete pRect2;
        }
    }
}

void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects) {
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pPlayer->getPosition().getX();
    pRect1->y = pPlayer->getPosition().getY();
    pRect1->w = pPlayer->getWidth();
    pRect1->h = pPlayer->getHeight();
    
    for(int i = 0; i < objects.size(); i++) {
        if(objects[i]->type() != std::string("Enemy") || !objects[i]->updating()) {
            continue;
        }
        
        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = objects[i]->getPosition().getX();
        pRect2->y = objects[i]->getPosition().getY();
        pRect2->w = objects[i]->getWidth();
        pRect2->h = objects[i]->getHeight();
        
        if(RectRect(pRect1, pRect2)) {
            if(!objects[i]->dead() && !objects[i]->dying()) {
                pPlayer->collision();
            }
        }
        
        delete pRect2;
    }
    
    delete pRect1;
}

void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers) {
    for(std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it) {
        TileLayer* pTileLayer = (*it);
        std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();
        
        Vector2D layerPos = pTileLayer->getPosition();
        
        int x, y, tileColumn, tileRow, tileid = 0;
        
        x = layerPos.getX() / pTileLayer->getTileSize();
        y = layerPos.getY() / pTileLayer->getTileSize();
        
        if(pPlayer->getVelocity().getX() >= 0 || pPlayer->getVelocity().getY() >= 0) {
            tileColumn = ((pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize());
            tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
            tileid = tiles[tileRow + y][tileColumn + x];
        }
        else if(pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0) {
            tileColumn = pPlayer->getPosition().getX() / pTileLayer->getTileSize();
            tileRow = pPlayer->getPosition().getY() / pTileLayer->getTileSize();
            tileid = tiles[tileRow + y][tileColumn + x];
        }
        
        if(tileid != 0) {
            pPlayer->collision();
        }
    }
}