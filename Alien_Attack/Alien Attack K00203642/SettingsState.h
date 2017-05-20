/*
	SettingsState.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/03/16	Created settings menu, with option to turn on off music and make game view Full Screen / Windowed
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include "GameState.h"
#include "Level.h"
#include <vector>
#include "MenuState.h"

class GameObject;
class SDLGameObject;

class SettingsState : public MenuState {
public:

	virtual ~SettingsState() { }

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_SettingsID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	void selectCurrentButton();											// Select the current button for gamepad/keyboard selection

private:
	static void s_settingsToMain();		// Go To Main Menu state
	static void s_fullScreen();			// Make the game full screen
	static void s_musicOnOff();			// Turn music off
	static void s_volumeUp();			// Turn the volume up
	static void s_volumeDown();			// Turn the volume down

	static const std::string s_SettingsID;

	std::vector<GameObject*> m_gameObjects;
};


#endif
