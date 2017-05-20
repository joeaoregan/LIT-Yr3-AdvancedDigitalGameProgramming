/*
	Game.h
	SDL Game Programming Book
	
	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/22	Adjusted screen size to 800 x 510
		2017/03/23	Moved window flag to Game.h to keep track of window Full Screen/Windowed mode
		2017/02/25	Added a name variable for Player for use with High Scores table

*/

#ifndef __SDL_Game_Programming_Book__Game__
#define __SDL_Game_Programming_Book__Game__

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640	// 2017/04/23 Changed from 510 to 640 after changing number of tiles to 150x20

#include "SDL.h"
#include "GameStateMachine.h"
//#include "SDL_mixer.h"
#include <cstdlib>			// 2017/04/22 For Random Numbers
#include <ctime>			// 2017/04/22 For Random Numbers
#include <vector>

class Game {
public:    
    static Game* Instance() {
        if(s_pInstance == 0) {
            s_pInstance = new Game();
            return s_pInstance;
        }
        
        return s_pInstance;
    }

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void render();
    void update();
    void handleEvents();
    void clean();
    
    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    SDL_Window* getWindow() const { return m_pWindow; }
    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

    /* 2017/03/23 Change between Full Screen / Windowed */
	int windowFlag = 0;
	void fullScreenOrWindowed();

    void setPlayerLives(int lives) { m_playerLives = lives; }
    int getPlayerLives() { return m_playerLives; }
    
    void setCurrentLevel(int currentLevel);
    const int getCurrentLevel() { return m_currentLevel; }
    
    void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
    const int getNextLevel() { return m_nextLevel; }
    
    void setLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }
    const bool getLevelComplete() { return m_bLevelComplete; }
    
    bool running() { return m_bRunning; }
    
    void quit() { m_bRunning = false; }
    
    int getGameWidth() const { return m_gameWidth; }
    int getGameHeight() const { return m_gameHeight; }
    float getScrollSpeed() { return m_scrollSpeed; }

	bool changingState() { return m_bChangingState; }
	void changingState(bool cs) { m_bChangingState = cs; }
    
    std::vector<std::string> getLevelFiles() { return m_levelFiles; }

	// Player Name
	std::string getPlayerName() { return m_plName; }			// 2017/04/16 Moved to GameObject
	void setPlayerName(std::string n) { m_plName = n; }			// 2017/04/16 Moved to GameObject

	// Player Score
	int getScore() { return m_score; }							// Get the players score (time played)
	void setScore(int s) { m_score = s; }						// Set the players score

	bool getEnterTextState() { return enterTextState; };		// 2017/04/22 Indicates if in enter text state or not
	void setEnterTextState(bool ts) { enterTextState = ts; };	// 2017/04/22 Set the game as in or out of enter text state

	// 2017/04/23 Set the players position on mini map
	//int getMapX() { return playerMapX; };
	//int getMapY() { return playerMapY; };
	int playerX, playerY, playerMapX;							// Keep track of player position for Mini Map and Enemy Tracking
	float totalScrolledDistance;								// Total scrolling distance needs to be added to the players x coordinate, to give distance on map

	int turretKills;											// Number of turrets killed by the player
	
private:
		
	bool enterTextState;						// 2017/04/22 If in the enter text state, allow text to be entered

	std::string m_plName;						// 2017/02/25 Name for player // 2017/04/16 Moved to GameObject

	bool m_bChangingState;
    
    SDL_Window* m_pWindow;						// Game window
    SDL_Renderer* m_pRenderer;					// Render graphics
    
    GameStateMachine* m_pGameStateMachine;		// State machine
    
    bool m_bRunning;
    
    static Game* s_pInstance;
    
    int m_gameWidth;
    int m_gameHeight;
    float m_scrollSpeed;						// Scroll speed used for minimap (0.8)
    
    int m_playerLives;
    
    int m_currentLevel;
    int m_nextLevel;
    bool m_bLevelComplete;
    
    std::vector<std::string> m_levelFiles;
    
    Game();
    ~Game();
    
    Game(const Game&);
	Game& operator=(const Game&);

	int m_score;
};

typedef Game TheGame;

#endif /* defined(__SDL_Game_Programming_Book__Game__) */
