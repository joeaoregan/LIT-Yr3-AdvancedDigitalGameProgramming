/*
	2017/03/16 Settings state
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include "GameState.h"
#include "Level.h"
#include <vector>
#include "MenuState.h"

class GameObject;
class SDLGameObject;

class Settings : public MenuState {
public:

	virtual ~Settings() { }

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_SettingsID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static void s_settingsToMain();

	static const std::string s_SettingsID;

	std::vector<GameObject*> m_gameObjects;
};


#endif
