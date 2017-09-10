/*
//  TextureManager.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 31/12/2012.
//  Copyright (c) 2012 shaun mitchell. All rights reserved.
*/
#include "TextureManager.h"
#include "SDL_image.h"
#include "SDL.h"
//#include <SDL_ttf.h>	// 16/02/2017 Add font

TextureManager* TextureManager::s_pInstance = 0;

SDL_Surface* textSurface;

#ifdef _SDL_TTF_H
bool TextureManager::loadFromRenderedText(std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, SDL_Renderer* pRenderer, bool textWrapped) {
	free();	//Get rid of preexisting texture

	if (!textWrapped) textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);	//Render text surface
	else textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 1000);

	if (textSurface != NULL) {
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);

		if (mTexture == NULL) {
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

	if (mTexture != 0) {
		m_textureMap[id] = mTexture;
		return true;
	}

	std::cout << "NOT WORKING" << std::endl;
	return false;
}
#endif

void TextureManager::free() {
	// Free texture if it exists
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    
    if(pTempSurface == 0) {
		std::cout << IMG_GetError();
        return false;
    }
    
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    
    SDL_FreeSurface(pTempSurface);
    
    if(pTexture != 0) {
        m_textureMap[id] = pTexture;
        return true;
    }
    
    return false;
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

