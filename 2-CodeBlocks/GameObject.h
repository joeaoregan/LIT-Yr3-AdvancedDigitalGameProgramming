/*
	GameObject.h
	SDL Game Programming Book

	Created by shaun mitchell on 09/02/2013.
    Copyright (c) 2013 shaun mitchell. All rights reserved.
	
	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/25	Added m_type variable to distinguish types of game objects
		2017/04/22	Added m_health variable to keep track of health, 
					kill() function to set m_bDead to true, 
					and m_currentFrame to get the current animation frame
		2017/04/16	Added name field to identify Game Objects
*/

#ifndef SDL_Game_Programming_Book_GameObject_h
#define SDL_Game_Programming_Book_GameObject_h

#include "LoaderParams.h"
#include "Vector2D.h"
#include <string>
#include <memory>

enum gameObjectTypes { PLAYER, EVERYTHING_ELSE };	// 2017/04/25 set m_type for game objects

class GameObject {
public:       
    virtual ~GameObject() {}			// base class needs virtual destructor
    
    // load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
    virtual void load(std::unique_ptr<LoaderParams> const &pParams)=0;
        
    virtual void draw()=0;				// draw the object
        
    virtual void update()=0;			// do update stuff
    
    virtual void clean()=0;				// remove anything that needs to be deleted
    
    virtual void collision() = 0;		// object has collided, handle accordingly
    

    virtual std::string type() = 0;		// get the type of the object
    
    // getters for common variables
    Vector2D& getPosition() { return m_position; }
    Vector2D& getVelocity() { return m_velocity; }
    
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
    
    // scroll along with tile map
    void scroll(float scrollSpeed)  {
        if(type() != std::string("Player"))						// player is never scrolled
        {
            m_position.setX(m_position.getX() - scrollSpeed);
        }
    }
        
    bool updating() { return m_bUpdating; }						// is the object currently being updated?
       
    bool dead() { return m_bDead; }								// is the object dead?
	void kill() { m_bDead = true; }								// 2017/04/22 Kill the object

	bool dying() { return m_bDying; }							// is the object doing a death animation?
        
    void setUpdating(bool updating) { m_bUpdating = updating; }	// set whether to update the object or not

	//2017/02/05 Added getter setter methods for name variable 2017/04/16 Moved from Player class
	std::string getName() { return m_name; }
	void setName(std::string n) { m_name = n; }

	// 2017/04/16 Added getter / setter methods for texture id
	std::string getTextureID() { return m_textureID; }			// 2017/04/16 get the texture ID
	void setTextureID(std::string id) { m_textureID = id; }		// 2017/04/16 set the texture ID

	int getCurrentFrame() { return m_currentFrame; };			// 2017/04/22 Get the current frame
	void setCurrentFrame(int cf) { m_currentFrame = cf; };		// 2017/04/22 Set the current frame
		
	int getType() { return m_type; };							// 2017/04/25 Get the type
	void setType(int t) { m_type = t; };						// 2017/04/25 Set the type
        
protected:    
    // constructor with default initialisation list
	GameObject() : m_position(0, 0),
		m_velocity(0, 0),
		m_acceleration(0, 0),
		m_width(0),
		m_height(0),
		m_currentRow(0),
		m_currentFrame(0),
		m_bUpdating(false),
		m_bDead(false),
		m_bDying(false),
		m_angle(0),
		m_alpha(255),
		m_time(0),
		m_health(100),				// 2017/04/22 Set the health to 100
		m_score(5)					// Score for the object
		//m_scoreSet(false)			// Is the score set
    {
    }

	//bool m_scoreSet;				// 2017/04/27 Score constantly updates

	int m_health;					// 2017/04/22 Health value for an object // Already in Enemy

	int m_score;					// Score value for an object

    // movement variables
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;
    
	std::string m_name;				// 2017/02/25 Added name to identify Game Objects // 2017/04/16 Moved from Player class
	int m_type;						// 2017/02/25 distinguish between game objects

    // size variables
    int m_width;
    int m_height;
    
    // animation variables
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;		// ID for sprite texture
    
    // common boolean variables
    bool m_bUpdating;
    bool m_bDead;
    bool m_bDying;
        
    double m_angle;	// rotation
        
    int m_alpha;	// blending

	unsigned int m_time;
};	

#endif