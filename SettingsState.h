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
	static void s_volumeUpMusic();		// 2017/04/25 Turn the music volume up	(Range is 0 to 128 for volumes)
	static void s_volumeDownMusic();	// 2017/04/25 Turn the music volume down
	static void s_volumeUpEffects();	// 2017/04/25 Turn the effects volume up
	static void s_volumeDownEffects();	// 2017/04/25 Turn the effects volume down
	static void s_increaseDifficulty();	// 2017/04/25 Increase the game difficulty (Range is Liam to Hard for difficulty)
	static void s_decreaseDifficulty(); // 2017/04/25 Decrease the game difficulty

	static const std::string s_SettingsID;

	std::vector<GameObject*> m_gameObjects;
};


#endif