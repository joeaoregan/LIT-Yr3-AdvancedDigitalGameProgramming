/*
	HighScoreState.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/02/03	Created High Scores Table that reads to and writes from a text file
*/

#ifndef HIGH_SCORE_STATE_H
#define HIGH_SCORE_STATE_H

#include "GameState.h"
#include "Level.h"
#include <vector>
#include "MenuState.h"

class GameObject;
class SDLGameObject;

class HighScoreState : public MenuState {
public:

	virtual ~HighScoreState() { }

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_HighScoreID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static void s_highscoresToMain();

	static const std::string s_HighScoreID;

	std::vector<GameObject*> m_gameObjects;
};


#endif
