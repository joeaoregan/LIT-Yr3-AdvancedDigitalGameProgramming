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
#include "Level.h"
#include <vector>
#include "MenuState.h"

class GameObject;
class SDLGameObject;

class EnterNameState : public MenuState {
public:

	virtual ~EnterNameState() { }

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_EnterNameID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static void s_enterNameToMain();
	static void s_enterNameToGame();

	static const std::string s_EnterNameID;

	std::vector<GameObject*> m_gameObjects;
};


#endif
