/*
	TitleScreenState.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/24	Created Title Screen State because I deserve credit for everything (and a small bit Shaun Mitchell)
*/

#ifndef TITLE_H
#define TITLE_H

#include "GameState.h"
#include "Level.h"
#include <vector>
#include "MenuState.h"

class GameObject;
class SDLGameObject;

class TitleScreenState : public MenuState {
public:

	virtual ~TitleScreenState() { }

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_TitleID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static void s_titleToMenu();	// Proceed to main menu
	static void s_exitFromTitle();	// Exit the game

	static const std::string s_TitleID;

	std::vector<GameObject*> m_gameObjects;
};


#endif
