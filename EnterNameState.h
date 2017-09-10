/*
	EnterNameState.h

	Created by : Joe O'Regan
	Student Number : K00203642

	Done :
		2017/04/22	Created state for entering name, as entering text has a lot of overhead, and text requires a number of button presses for each character
*/

#ifndef ENTER_NAME_STATE_H
#define ENTER_NAME_STATE_H

#include "GameState.h"
#include <iostream>
#include <vector>
#include "MenuState.h"

class GameObject;

class EnterNameState : public MenuState {
public:
	virtual ~EnterNameState() {}
	/*
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
	*/
	virtual void update() {};
	virtual void render() {};

	virtual bool onEnter() {};
	virtual bool onExit() {};

	virtual std::string getStateID() const { return s_nameID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:

	static void s_nameToGame();
	static void s_returnToMenu();

	static const std::string s_nameID;

	std::vector<GameObject*> m_gameObjects;
}

#endif