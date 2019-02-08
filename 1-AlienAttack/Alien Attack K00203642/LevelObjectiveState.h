/*
	LevelObjectiveState.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/25	Created Level objective state, to inform player killing 7 turrets = points bonus for Level 1, other objectives can be added
*/

#ifndef LEVEL_OBJECTIVES_H
#define LEVEL_OBJECTIVES_H

#include "GameState.h"
#include "Level.h"
#include <vector>
#include "MenuState.h"

class GameObject;
class SDLGameObject;

class LevelObjectiveState : public MenuState {
public:

	virtual ~LevelObjectiveState() { }

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_ObjectiveID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static void s_objectiveToGame();	// Proceed to game
	static void s_objectiveToMenu();	// Exit the game

	static const std::string s_ObjectiveID;

	std::vector<GameObject*> m_gameObjects;
};


#endif
