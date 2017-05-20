/*
//  CollisionManager.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 28/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by : Joe O'Regan
	Student Number : K00203642

	Done :
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
    
    void checkPlayerEnemyBulletCollision(Player* pPlayer);
    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*>& objects);
    void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);
};

#endif /* defined(__SDL_Game_Programming_Book__CollisionManager__) */
