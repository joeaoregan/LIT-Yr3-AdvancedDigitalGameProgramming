/*
	TextureManager.cpp
	SDL Game Programming Book

	Created by shaun mitchell on 31/12/2012.
	Copyright (c) 2012 shaun mitchell. All rights reserved.

	Modified by:	Joe O'Regan 
	Student Number:	K00203642

	Done:
		2017/04/22	Included Game class to use renderer directly in functions instead of passing it in
		2017/02/25	fstream added to read in high scores from file to render to screen using loadFromRenderedText() in TextureManager class
*/
#include "TextureManager.h"
#include "SDL_image.h"
#include "SDL.h"
#include <iomanip>
#include <sstream>		// For timer
#include <fstream>		// 2017/02/25 Read high scores from file

#include "Game.h"		// 2017/04/22	Added to include renderer in functions

//#include <SDL_ttf.h>	// 16/02/2017 Add font

TextureManager* TextureManager::s_pInstance = 0;

SDL_Surface* textSurface;

void TextureManager::drawText(std::string id, int x, int y, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;	

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = m_Width;
	srcRect.h = destRect.h = m_Height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

/*
	Enter Name State text functions
*/
void Texture::loadEnterNameText(std::string nameText) {
	SDL_Texture* enterNameTexture = 0;	// The actual hardware texture
	createText(enterNameTexture, nameText, "enterNameID", { 0, 0, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);	// Player Enter Name
}
void Texture::loadInputText(std::string input) {
	free();
	SDL_Texture* inputTextTexture = 0;																						// The actual hardware texture
	createText(inputTextTexture, input, "inputTextID", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);	// Input text
}
void Texture::loadReturnToMenuText(std::string input) {
	SDL_Texture* tx2 = 0;																									// The actual hardware texture
	createText(tx2, input, "returnToMenuID", { 255, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);				// Get ready to start message
}

/*
	Play State text rendering functions
*/
void Texture::loadLevelText(std::string currentLevel) {	
	SDL_Texture* level = 0;																									// The actual hardware texture
	createText(level, currentLevel, "levelID", { 0, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 12));						// Current Level
}
void Texture::loadReadyText(std::string input) {
	SDL_Texture* readyTexture = 0;																							// The actual hardware texture
	createText(readyTexture, input, "readyID", { 255, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 24), true);				// Get ready to start message
}
void Texture::loadFinalScoreText(std::string input) {
	SDL_Texture* readyTexture = 0;																							// The actual hardware texture
	createText(readyTexture, input, "scoreID", { 255, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 24), true);				// Get ready to start message
}
void Texture::loadLevelTimeText(std::string input) {
	SDL_Texture* readyTexture = 0;																							// The actual hardware texture
	createText(readyTexture, input, "timeID", { 255, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 24), true);				// Get ready to start message
}

/* 
	Timer text rendering function
*/
void Texture::loadTimerText(std::string currentTime) {
	SDL_Texture* timerTexture = 0;
	createText(timerTexture, currentTime, "timerID", { 0, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));				// Game Timer
}

/*
	HUD text rendering functions

int previousTurrets = -1;	// Don't render the text every frame
void Texture::turretsKilledText(std::string input) {
	if (previousTurrets != Game::Instance()->turretKills) {
		free();
		free(tx1);
		std::string turrets = "Turrets: " + std::to_string(Game::Instance()->turretKills);
		createText(tx1, turrets + "/7", "turretsKilledID", { 0, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);	// Get ready to start message
		previousTurrets = Game::Instance()->turretKills;	// update the number of turrets
	}
}
void Texture::loadScoreText(std::string currentScore) {
	SDL_Texture* score = 0;	// The actual hardware texture
	createText(score, currentScore, "timerID", { 0, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 12), Game::Instance()->getRenderer());						// 2017/04/22 Score
}
*/
void Texture::displayDifficulty(int level) {
	/*
	std::string difficultyLevel;

	if (level == 0) {
	difficultyLevel = "Easy";
	}
	else if (level == 1) {
	difficultyLevel = "Medium";
	}
	else if (level == 2) {
	difficultyLevel = "Hard";
	}

	SDL_Texture* score = 0;	// The actual hardware texture
	createText(score, difficultyLevel, "difficultyID", { 0, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 12), Game::Instance()->getRenderer());						// 2017/04/22 Score
	*/
}
/*
	High Scores State text rendering function
*/
void TextureManager::loadHighScoresText() {
	std::string player;																										// Players name
	std::stringstream highScores;																							// Player score

	std::ifstream infile;																									// file to read in
	infile.open("scores.txt");																								// text file in assets folder

	std::cout << "Reading high scores from file" << std::endl;												
	
	struct PlayerScores {																									// Structure to hold name and score
		std::string name;
		int score;
	};

	PlayerScores temp;																										// temporary stuct for swapping new score into correct position in list
	PlayerScores scoreTable[11];																							// Array of 11 scores, 10 from file + new score to be sorted
	const int numScores = 10;																								// Total number of scores to display
	int eachScore = 0;																										// Iterator used to read in each score

	if (infile.is_open()) {																									// If the file is open
		//for (int i = 0; i < 10; i++){
		while(getline(infile, scoreTable[eachScore].name) && getline(infile, player) && eachScore <= numScores){			// While the iterator is less than the max number of lines to be read
			//getline(infile, player);

			scoreTable[eachScore].score = stoi(player);																		// Add score to struct array
			++eachScore;																									// increment the iterator
		}
		
		infile.close();																										// Close the file when done
	}

	//for (int i = 1; i < eachScore + 1; i++) {
	//	for (int j = 0; j < eachScore + 1 - i; j++) {
	for (int i = 1; i < eachScore; i++) {																					// Sort the array of Player Score structs
		for (int j = 0; j < eachScore - i; j++) {																			
			//if (strcmp(scoreTable[j].plname, scoreTable[j + 1].plname) > 0)
			if(scoreTable[j].score < scoreTable[j+1].score) {																// Sort Largest Score To Smallest in the struct
				temp = scoreTable[j];
				scoreTable[j] = scoreTable[j + 1];
				scoreTable[j + 1] = temp;
			}
		}
	}
	
	for (int i = 0; i < eachScore; i++) {																					// Format the output
		highScores << std::setw(3) << std::to_string(i + 1) << ". " << std::left << std::setw(14) << std::setfill('.') << scoreTable[i].name << std::right << std::setw(8) << std::to_string(scoreTable[i].score) << std::setfill(' ') << "\n";
	}

	if (eachScore <= 0) highScores << "No High Scores Recorded Yet!";

	// Render the name and score to a texture
	//std::string highScores = "Player 1:  10\nPlayer 2:  20\nPlayer 3:  30\nPlayer 4:  40\nPlayer 5:  50\nPlayer 6:  60\nPlayer 7:  70\nPlayer 8:  80\nPlayer 9:  90\nPlayer 10: 100";
	SDL_Texture* highScore = 0;	// The actual hardware texture
	createText(highScore, highScores.str().c_str(), "highScoresID", { 100, 100, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 24), true);
}

bool TextureManager::createText(std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, bool textWrapped) {
	free();	//Get rid of preexisting texture

	if (!textWrapped) textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);	//Render text surface
	else textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 1000);

	if (textSurface != NULL) {
		//Create texture from surface pixels
		//mTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
		m_Texture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), textSurface);

		//if (mTexture == NULL) {
		if (m_Texture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			//Get image dimensions
			m_Width = textSurface->w;
			m_Height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);	//Get rid of old surface
	}
	else {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//return mTexture != NULL;	// Return success

	//if (mTexture != 0) {
	if (m_Texture != 0) {
		//m_textureMap[id] = mTexture;	// Add to texture map
		m_textureMap[id] = m_Texture;	// Add to texture map
		return true;
	}

	std::cout << "NOT WORKING" << std::endl;
	return false;
}

bool TextureManager::createText(SDL_Texture* text, std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, bool textWrapped) {
	free();	//Get rid of preexisting texture

	if (!textWrapped) textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);	//Render text surface
	else textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 1000);

	if (textSurface != NULL) {
		//Create texture from surface pixels
		//mTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
		text = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), textSurface);

		//if (mTexture == NULL) {
		if (text == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			//Get image dimensions
			m_Width = textSurface->w;
			m_Height = textSurface->h;
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

bool TextureManager::loadText(std::string fileName, std::string id) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0) {
		std::cout << IMG_GetError();
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

bool TextureManager::load(std::string fileName, std::string id) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0) {
		std::cout << IMG_GetError();
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

void TextureManager::free() {
	// Free texture if it exists
	if (m_Texture != NULL) {
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}
}

void TextureManager::free(SDL_Texture *texture) {
	// Free texture if it exists
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
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

bool Texture::renderTextToTexture(std::string textureText, SDL_Color textColor, TTF_Font* font, std::string id, bool textWrapped) {
	free();	//Get rid of preexisting texture

	if (!textWrapped)
		m_TextSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);					// Render text surface
	else
		m_TextSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 1000);	// Render text surface with text wrapping

	if (m_TextSurface != NULL) {
		m_Texture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), m_TextSurface);		// Create texture from surface pixels

		if (m_Texture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			m_Width = m_TextSurface->w;	// Get image dimensions
			m_Height = m_TextSurface->h;
		}

		SDL_FreeSurface(m_TextSurface);	// Get rid of old surface
	}
	else {
		printf("loadFromRenderedText(): Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());	// Error message
	}

	if (id != "") {
		if (m_Texture != 0) {
			m_textureMap[id] = m_Texture;	// Add to texture map

			return true;
		}
	}

	return m_Texture != NULL;			// Return success
}

/*
	Render a texture
*/
void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };	// Set rendering space and render to screen

	if (clip != NULL) {									// Set clip rendering dimensions
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(Game::Instance()->getRenderer(), m_Texture, clip, &renderQuad, angle, center, flip);	// Render to screen
}
