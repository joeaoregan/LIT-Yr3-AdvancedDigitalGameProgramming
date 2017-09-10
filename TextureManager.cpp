/*
	TextureManager.cpp
	SDL Game Programming Book

	Created by shaun mitchell on 31/12/2012.
	Copyright (c) 2012 shaun mitchell. All rights reserved.

	Modified by:	Joe O'Regan 
	Student Number:	K00203642

	Done:
		2017/02/25 fstream added to read in high scores from file to render to screen using loadFromRenderedText() in TextureManager class
*/
#include "TextureManager.h"
#include "SDL_image.h"
#include "SDL.h"
#include <iomanip>
#include <sstream>		// For timer
#include <fstream>		// 2017/02/25 Read high scores from file

//#include <SDL_ttf.h>	// 16/02/2017 Add font

TextureManager* TextureManager::s_pInstance = 0;

SDL_Surface* textSurface;

void TextureManager::drawText(std::string id, int x, int y, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = mWidth;
	srcRect.h = destRect.h = mHeight;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::loadReadyText(std::string input, SDL_Renderer* rend) {
	SDL_Texture* readyTexture = 0;	// The actual hardware texture
	TheTextureManager::Instance()->loadFromRenderedText(readyTexture, input, "readyID", { 255, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), rend, true);		// Lives in top left corner
}
void TextureManager::loadInputText(std::string input, SDL_Renderer* rend) {
	SDL_Texture* inputTextTexture = 0;	// The actual hardware texture
	TheTextureManager::Instance()->loadFromRenderedText(inputTextTexture, input, "inputTextID", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), rend, true);		// Lives in top left corner
}
void TextureManager::loadEnterNameText(std::string nameText, SDL_Renderer* rend) {
	SDL_Texture* enterName = 0;	// The actual hardware texture
	TheTextureManager::Instance()->loadFromRenderedText(enterName, nameText, "enterNameID", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), rend, true);		// Lives in top left corner
}
void TextureManager::loadLevelText(std::string currentLevel, SDL_Renderer* rend) {
	SDL_Texture* level = 0;	// The actual hardware texture
	TheTextureManager::Instance()->loadFromRenderedText(level, currentLevel, "levelID", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), rend);		// Lives in top left corner
}
void TextureManager::loadScoreText(std::string currentScore, SDL_Renderer* rend) {
	SDL_Texture* score = 0;	// The actual hardware texture
	TheTextureManager::Instance()->loadFromRenderedText(score, currentScore, "timerID", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 12), rend);
}
void TextureManager::loadHighScoresText(SDL_Renderer* rend) {
	std::string player;
	std::stringstream highScores;

	std::ifstream infile;
	infile.open("scores.txt");

	std::cout << "Reading high scores from file" << std::endl;
	
	struct PlayerScores {
		std::string name;
		int score;
	};

	PlayerScores temp;

	const int numScores = 10;

	PlayerScores scoreTable[11];

	int eachScore = 0;

	if (infile.is_open()) {
		//for (int i = 0; i < 10; i++){
		while(getline(infile, scoreTable[eachScore].name) && getline(infile, player) && eachScore <= numScores){
			//getline(infile, player);

			scoreTable[eachScore].score = stoi(player);
			++eachScore;
		}
		
		infile.close();
	}

	//for (int i = 1; i < eachScore + 1; i++) {
	//	for (int j = 0; j < eachScore + 1 - i; j++) {
	for (int i = 1; i < eachScore; i++) {
		for (int j = 0; j < eachScore - i; j++) {
			//if (strcmp(scoreTable[j].plname, scoreTable[j + 1].plname) > 0)
			if(scoreTable[j].score < scoreTable[j+1].score) { // Sort Largest Score To Smallest in the struct
				temp = scoreTable[j];
				scoreTable[j] = scoreTable[j + 1];
				scoreTable[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < eachScore; i++) {
		highScores << std::setw(3) << std::to_string(i + 1) << ". " << std::left << std::setw(14) << std::setfill('.') << scoreTable[i].name << std::right << std::setw(8) << std::to_string(scoreTable[i].score) << std::setfill(' ') << "\n";
	}

	if (eachScore <= 0) highScores << "No High Scores Recorded Yet!";


	//std::string highScores = "Player 1:  10\nPlayer 2:  20\nPlayer 3:  30\nPlayer 4:  40\nPlayer 5:  50\nPlayer 6:  60\nPlayer 7:  70\nPlayer 8:  80\nPlayer 9:  90\nPlayer 10: 100";
	SDL_Texture* highScore = 0;	// The actual hardware texture
	TheTextureManager::Instance()->loadFromRenderedText(highScore, highScores.str().c_str(), "highScoresID", { 100, 100, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), rend, true);
}

bool TextureManager::loadFromRenderedText(SDL_Texture* text, std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, SDL_Renderer* pRenderer, bool textWrapped) {
	free();	//Get rid of preexisting texture

	if (!textWrapped) textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);	//Render text surface
	else textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 1000);

	if (textSurface != NULL) {
		//Create texture from surface pixels
		//mTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
		text = SDL_CreateTextureFromSurface(pRenderer, textSurface);

		//if (mTexture == NULL) {
		if (text == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);	//Get rid of old surface
	}
	else {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//return mTexture != NULL;	// Return success

	//if (mTexture != 0) {
	if (text != 0) {
		//m_textureMap[id] = mTexture;	// Add to texture map
		m_textureMap[id] = text;	// Add to texture map
		return true;
	}

	std::cout << "NOT WORKING" << std::endl;
	return false;
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0) {
		std::cout << IMG_GetError();
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

void TextureManager::free() {
	// Free texture if it exists
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}


void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}


void TextureManager::clearTextureMap() {
    m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(std::string id) {
    m_textureMap.erase(id);
}

