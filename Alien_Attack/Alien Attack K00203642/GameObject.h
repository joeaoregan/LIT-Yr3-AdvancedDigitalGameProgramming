/*
//  GameObject.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 06/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

Modified by Joe O'Regan
2017/02/25	Added name for GameObject
*/

#ifndef SDL_Game_Programming_Book_GameObject_h
#define SDL_Game_Programming_Book_GameObject_h

#include "LoaderParams.h"
#include "Vector2D.h"
#include <string>
#include <memory>

class GameObject {
public:
	virtual ~GameObject() {}	// base class needs virtual destructor

								// load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
	virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;

	virtual void draw() = 0;				// draw the object

	virtual void update() = 0;			// do update stuff

	virtual void clean() = 0;				 // remove anything that needs to be deleted

	virtual void collision() = 0;		 // object has collided, handle accordingly


	virtual std::string type() = 0;    // get the type of the object

									   // getters for common variables
	Vector2D& getPosition() { return m_position; }
	Vector2D& getVelocity() { return m_velocity; }

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	//std::string getName() { return m_name; }
	//void setName(std::string n) { m_name = n; }

	// scroll along with tile map
	void scroll(float scrollSpeed) {
		if (type() != std::string("Player")) // player is never scrolled
		{
			m_position.setX(m_position.getX() - scrollSpeed);
		}
	}

	bool updating() { return m_bUpdating; }						// is the object currently being updated?

	bool dead() { return m_bDead; }								// is the object dead?

	bool dying() { return m_bDying; }							// is the object doing a death animation?

	void setUpdating(bool updating) { m_bUpdating = updating; }	// set whether to update the object or not

protected:
	// constructor with default initialisation list
	GameObject() : m_position(0, 0),
		m_velocity(0, 0),
		m_acceleration(0, 0),
		m_width(0),
		m_height(0),
		m_currentRow(0),
		m_currentFrame(0),
		m_bUpdating(false),
		m_bDead(false),
		m_bDying(false),
		m_angle(0),
		m_alpha(255),
		m_time(0)
	{
	}

	int m_score;		// Score value for an object

						// movement variables
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	// size variables
	int m_width;
	int m_height;

	// animation variables
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
	std::string m_textureID;

	// common boolean variables
	bool m_bUpdating;
	bool m_bDead;
	bool m_bDying;

	double m_angle;	// rotation

	int m_alpha;	// blending

	unsigned int m_time;

	std::string m_name;
};

#endif