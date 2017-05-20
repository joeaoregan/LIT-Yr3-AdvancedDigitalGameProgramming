/*
    TextureManager.h
    SDL Game Programming Book
  
    Created by shaun mitchell on 31/12/2012.
    Copyright (c) 2012 shaun mitchell. All rights reserved.
	
	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/03/16	Added SDL_ttf to render text to textures
					Added custom functions for rendering text for timer and level
*/

#ifndef __TextureManager__
#define __TextureManager__

#include <iostream>
#include <string>
#include <map>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>	// 16/02/2017 Add font

class TextureManager {
public:    
    static TextureManager* Instance() {
        if(s_pInstance == 0) {
            s_pInstance = new TextureManager();
            return s_pInstance;
        }
       
        return s_pInstance;
    }

#ifdef _SDL_TTF_H
	//Creates image from font string
	void loadReturnToMenuText(std::string input);	// 2017/04/22 Message Player return to menu
	void loadReadyText(std::string input);			// Message Player ready to start
	void loadInputText(std::string input);			// Text input by player
	void loadEnterNameText(std::string enterName);	// Message to enter name
	void loadLevelText(std::string currentLevel);	// Display the current level
	void loadTimerText(std::string currentTime);	// Display the game timer
	void loadScoreText(std::string currentScore);	// Display the score

	void loadHighScoresText();
	bool createText(SDL_Texture* text, std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, SDL_Renderer* rend, bool textWrapped = false);
#endif

	void free();												// Deallocates texture

    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
    
    void clearTextureMap();
    void clearFromTextureMap(std::string id);

	void drawText(std::string id, int x, int y, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);	// 25/02/2017 render function for text

	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);
    
    std::map<std::string, SDL_Texture*> getTextureMap() { return m_textureMap; }

	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }
    
private:
    
    TextureManager() {}
    ~TextureManager() {}
    
    TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);
    
    std::map<std::string, SDL_Texture*> m_textureMap;
    
    static TextureManager* s_pInstance;

	// 16/02/2017
	SDL_Texture* mTexture;	// The actual hardware texture

	int mWidth;		// Texture width
	int mHeight;	// Texture height
};

typedef TextureManager TheTextureManager;
typedef TextureManager Texture;

#endif /* defined(__SDL_Game_Programming_Book__TextureManager__) */
