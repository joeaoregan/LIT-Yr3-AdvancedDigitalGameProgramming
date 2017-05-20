/*
	Message.h

	Created by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/22	Added Message class
*/

#ifndef TIMER_H
#define TIMER_H

#include "GameObject.h"
#include <sstream>					// For timer
#include "Game.h"

class Message : public GameObject {
public:
	// Constructor
	Message() {
		setName("Message");
		std::cout << getName() << " created" << std::endl;

		m_bDead = false;	//2017/04/16 Set object alive
	}

	~Message() {
		std::cout << getName() << " destroyed!!!" << std::endl;
	}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams) {};

	virtual void update() {};

	virtual void draw() {};

	virtual void clean() {};
	
	virtual void collision() {};
};

#endif
