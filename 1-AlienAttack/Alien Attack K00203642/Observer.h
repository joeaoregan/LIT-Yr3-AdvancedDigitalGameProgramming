/*
	2017/04/25 Joe made this

	Observer virtual base class
*/

#include <SDL.h>
//#include "GameObject.h"

enum playerActions { MESSAGE1, MESSAGE2 };

class Observer {
public:
	virtual ~Observer() {}
	//virtual void whenNotified(const GameObject& gameobject, SDL_Event& e) = 0;			// Pure virtual notify recieved function
	virtual void whenNotified(int action) = 0;	// Pure virtual notify recieved function	// Only Player observing
};

