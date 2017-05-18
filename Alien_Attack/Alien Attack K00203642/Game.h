/*
//  Game.h
//  SDL Game Programming Book
//

	Modified by Joe O'Regan	
		2017/02/25 Added name and score variables for Player
*/

#ifndef __SDL_Game_Programming_Book__Game__
#define __SDL_Game_Programming_Book__Game__

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 480

#include "SDL.h"
#include "GameStateMachine.h"
//#include "SDL_mixer.h"
#include <vector>

class Game {
public:
	static Game* Instance() {
		if (s_pInstance == 0) {
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
	std::string getName() { return m_name; } 	// 2017/02/25
	void setName(std::string n) { m_name = n; }	// 2017/02/25
												// Player Score
	int getScore() { return m_score; }			// 2017/02/25
	void setScore(int s) { m_score = s; }		// 2017/02/25

private:
	bool m_bChangingState;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	GameStateMachine* m_pGameStateMachine;

	bool m_bRunning;

	static Game* s_pInstance;

	int m_gameWidth;
	int m_gameHeight;
	float m_scrollSpeed;

	int m_playerLives;

	int m_currentLevel;
	int m_nextLevel;
	bool m_bLevelComplete;

	std::vector<std::string> m_levelFiles;

	Game();
	~Game();

	Game(const Game&);
	Game& operator=(const Game&);

	std::string m_name;	// 2017/02/25 Name for player
	int m_score;		// 2017/02/25 Score for Player
};

typedef Game TheGame;

#endif /* defined(__SDL_Game_Programming_Book__Game__) */