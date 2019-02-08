/*
	LevelCompleteState.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/26	Displays the information at the end of the level
*/

#ifndef TITLE_H
#define TITLE_H

#include "GameState.h"
#include "Level.h"
#include <vector>
#include "MenuState.h"

class GameObject;
class SDLGameObject;

class LevelCompleteState : public MenuState {
public:

	virtual ~LevelCompleteState() { }

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_CompleteID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static void s_completeToNextLevel();	// Proceed to next level

	static const std::string s_CompleteID;

	std::vector<GameObject*> m_gameObjects;
};


#endif
