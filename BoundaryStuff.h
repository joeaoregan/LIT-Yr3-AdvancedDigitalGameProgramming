/*
	2017/04/25 Joe made this


#include <SDL.h>
#include "Observer.h"
#include "GameObject.h"
#include "Message.h"


// Observer Virtual Base Class

class BoundaryStuff : public Observer {							// Boundary Stuff class is a sub type of the Observer class
public:
	~BoundaryStuff() {											// Destructor
	}

	//virtual void whenNotified(const GameObject& gameobject, int action) {	// Inherits pure virtual notify recieved function
	virtual void whenNotified(int action) {	// Inherits pure virtual notify recieved function // Only Player observing
		if (action == MESSAGE1) {
			std::cout << "Action 1 has happened" << std::endl;
			displayMessage1();
		}
		else if (action == MESSAGE2) {
			std::cout << "Action 2 has happened" << std::endl;
			displayMessage2();
		}
	}

private:
	void displayMessage1() {
		std::cout << "Message for observation 1" << std::endl;
	}
	void displayMessage2() {
		std::cout << "Message for observation 2" << std::endl;
	}
};

*/
