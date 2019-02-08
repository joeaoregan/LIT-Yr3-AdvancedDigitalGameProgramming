/*
//  CollisionManager.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 28/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by : Joe O'Regan
	Student Number : K00203642

	Done :
		2017/04/23	Added check for collision between Player and Power Ups
		2017/04/22	Added most recent object collided with variable to adjust collision functionality for health, and health bar
*/

#ifndef __SDL_Game_Programming_Book__CollisionManager__
#define __SDL_Game_Programming_Book__CollisionManager__

#include <iostream>
#include <vector>

class Player;
class GameObject;
class TileLayer;

class CollisionManager {
public:
	void checkPlayerPowerUpCollision(Player* pPlayer, const std::vector<GameObject*> &objects);			// 2017/04/22 Check Player collisions with Power Ups

    void checkPlayerEnemyBulletCollision(Player* pPlayer);												// Check Player collisions with Enemy Bullets
    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);			// Check Player collisions with Enemies
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*>& objects);						// Check Enemy collisions with Player Bullets
    void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);		// Check Player collisions with Tiles
};

#endif /* defined(__SDL_Game_Programming_Book__CollisionManager__) */
