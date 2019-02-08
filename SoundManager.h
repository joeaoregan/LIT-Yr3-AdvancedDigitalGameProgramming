/*
    SoundManager.h
    SDL Game Programming Book
  
    Created by shaun mitchell on 26/03/2013.
    Copyright (c) 2013 shaun mitchell. All rights reserved.
	
	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/03/16	Added pausePlayMusic() function to pause the original music in the game
					by pressing the m key. Music can also be turned on / off in the settings menu
					Added playMusic() function to play the music selecting a random song from a list of songs
*/

#ifndef __SDL_Game_Programming_Book__SoundManager__
#define __SDL_Game_Programming_Book__SoundManager__

#define NUMBER_OF_SONGS 3;	// 2017/03/16 Number of songs in game

#include <iostream>
#include <map>
#include <string>
#include "SDL_mixer.h"

enum sound_type {
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager {
public:    
    static SoundManager* Instance() {
        if(s_pInstance == 0) {
            s_pInstance = new SoundManager();
            return s_pInstance;
        }
        return s_pInstance;
    }
    
    bool load(std::string fileName, std::string id, sound_type type);
    
    void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);
	void playMusic(int song = 0);
	void pausePlayMusic();						// 2017/03/16 Function to stop the music playing

	void trackForwards();						// 2017/04/23	Skip the track forwards
	void trackBackwards();						// 2017/04/23	Skip the track backwards

	// Adjust volumes
	void volumeUpMusic();
	void volumeDownMusic();
	void volumeUpEffects();
	void volumeDownEffects();

	int getVolumeMusic() { return volumeMusic; };			// 2017/04/25	Use volume for settings volume bar
	void setVolumeMusic(int v) { volumeMusic = v; };		// 2017/04/25	Set the volume
	int getVolumeEffects() { return volumeEffects; };		// 2017/04/25	Use volume for settings volume bar
	void setVolumeEffects(int v) { volumeEffects = v; };	// 2017/04/25	Set the volume

	void setFXvolumes(int v);								// Set the individual effects volumes
	    	
private:    

	int currentSong;							// Keep track of current song

    static SoundManager* s_pInstance;
    
    std::map<std::string, Mix_Chunk*> m_sfxs;
    std::map<std::string, Mix_Music*> m_music;
    
    SoundManager();
    ~SoundManager();
    
    SoundManager(const SoundManager&);
	SoundManager& operator=(const SoundManager&);

	int volumeMusic;			// 2017/04/25 Max volume is 128
	int volumeEffects;			// 2017/04/25 Max volume is 128
};

typedef SoundManager TheSoundManager;

#endif /* defined(__SDL_Game_Programming_Book__SoundManager__) */
