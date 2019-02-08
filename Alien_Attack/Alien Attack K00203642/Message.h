/*
	Message.h

	Created by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/26	Player (Subject) sends notifications to Message (Observer) for which Message displays the relevant message on screen
		2017/04/22	Added Message class
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include "GameObject.h"
#include <sstream>					// For timer
#include "Game.h"
#include "TextureManager.h"

#include "Observer.h"

// Message observes the subject Player
class Message : public GameObject, public Observer {
//class Message : public GameObject {
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

	virtual void load(std::unique_ptr<LoaderParams> const &pParams) {
		
	};

	virtual void update() {
	};

	virtual void draw() {
		//std::cout << actionToTake << std::endl;
		//if (actionToTake == 0) {
		//Texture::Instance()->draw("grass", 190, 215, 420, 50, Game::Instance()->getRenderer());
		//	std::cout << "Test 0" << std::endl;
		//}
		//if (actionToTake == 1) {
		if (Game::Instance()->observerMessage) {
			Texture::Instance()->draw("grass", 190, 215, 420, 50, Game::Instance()->getRenderer());
			//std::cout << "Test " << std::endl;
		}
	};

	virtual void clean() {};
	
	virtual void collision() {};
	

	// 2017/04/25 Observer Stuff
	void whenNotified(int action) {
		if (action == MESSAGE1)
			//std::cout << "Player is up " << action << std::endl;
		//	actionToTake = 2;
			Game::Instance()->observerMessage = false;
		else if (action == MESSAGE2) {
			//actionToTake = 1;
			//std::cout << "You're gonna crash!!!" << std::endl;
			//Texture::Instance()->draw("grass", 190, 215, 420, 50, Game::Instance()->getRenderer());
			//std::cout << "Player is down " << action << std::endl;
			Game::Instance()->observerMessage = true;
		}
	};

	virtual std::string type() {
		return "message";
	};

private:
	int actionToTake = 0;	// Stays 0 outside whenNotified
};

class MessageCreator : public BaseCreator {
	GameObject* createGameObject() const {
		return new Message();
	}
};
#endif
