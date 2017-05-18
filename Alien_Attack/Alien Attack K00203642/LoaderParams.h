//
//  LoaderParams.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 19/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef SDL_Game_Programming_Book_LoaderParams_h
#define SDL_Game_Programming_Book_LoaderParams_h

#include <string>

class LoaderParams {
public:
	LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames,
		int callbackID = 0, int animSpeed = 0, int score = 0) :
		m_x(x),
		m_y(y),
		m_width(width),
		m_height(height),
		m_textureID(textureID),
		m_numFrames(numFrames),
		m_callbackID(callbackID),
		m_animSpeed(animSpeed),
		m_score(score)
	{

	}

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string getTextureID() const { return m_textureID; }
	int getNumFrames() const { return m_numFrames; }
	int getCallbackID() const { return m_callbackID; }
	int getAnimSpeed() const { return m_animSpeed; }

private:
	int m_x, m_y;				// Coordinates

	int m_width, m_height;		// Diemensions

	int m_callbackID;
	int m_animSpeed;

	std::string m_textureID;	// Name for texture

	int m_numFrames;			// Number of frames in sprite sheet

	int m_score;				// Score for object
};

#endif