/*
	InstructionsState.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/24	Created Instructions State to view game controls
*/

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "GameState.h"
#include "Level.h"
#include <vector>
#include "MenuState.h"

class GameObject;
class SDLGameObject;

class InstructionsState : public MenuState {
public:

	virtual ~InstructionsState() { }

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_InstructionID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static void s_instructionsToMain();

	static const std::string s_InstructionID;

	std::vector<GameObject*> m_gameObjects;
};


#endif
