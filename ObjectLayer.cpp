/*
//  ObjectLayer.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 10/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/23	Added check for collision between Player and Power Ups
*/

#include "ObjectLayer.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Game.h"
#include "Level.h"

ObjectLayer::~ObjectLayer() {
    for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)// < m_gameObjects.size(); i++)
    {
        delete (*it);
    }
    m_gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel) {
    m_collisionManager.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
    m_collisionManager.checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)m_gameObjects);
	m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);
	m_collisionManager.checkPlayerPowerUpCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects); // 2017/04/22 Check Player collisions with Power Ups

	if(pLevel->getPlayer()->getPosition().getX() + pLevel->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth()) {
		m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());
	}
    
    // iterate through the objects
    if(!m_gameObjects.empty()) {
        for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)// < m_gameObjects.size(); i++)
        {
            if((*it)->getPosition().getX() <= TheGame::Instance()->getGameWidth()) {	// When the GameObject arrives on screen update it
                (*it)->setUpdating(true);													
                (*it)->update();
            }
            else {
                if((*it)->type() != std::string("Player")) {							// If the object is not the Player
                    (*it)->setUpdating(false);											// Don't update its movment
                    (*it)->scroll(TheGame::Instance()->getScrollSpeed());				// Scroll with background

                }
                else {
                    (*it)->update();	// Update the player
                }
            }
            
            // check if dead or off screen
            if((*it)->getPosition().getX() < (0 - (*it)->getWidth()) || (*it)->getPosition().getY() > (TheGame::Instance()->getGameHeight()) || ((*it)->dead())) {
                delete * it;
                it = m_gameObjects.erase(it); // erase from vector and get new iterator
            }
            else {
                ++it; // increment if all ok
            }            
        }
    }
}

void ObjectLayer::render() {
    for(int i = 0; i < m_gameObjects.size(); i++) {
        if(m_gameObjects[i]->getPosition().getX() <= TheGame::Instance()->getGameWidth()) {
            m_gameObjects[i]->draw();
        }
    }
}