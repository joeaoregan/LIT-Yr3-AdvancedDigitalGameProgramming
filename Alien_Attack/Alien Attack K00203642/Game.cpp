/*
	Game.cpp
	SDL Game Programming Book

	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/03/23	Pressing F11 or the Full Screen button in the settings menu Toggles between Full Screen and Windowed view of the game
					Added function to change between Full Screen and Windowed view
		2017/03/16	The music button in the Settings Menu turns the music On / Off
					Added some original songs to the game
					Added function to play a random song !!!!!!FIX THIS!!!!!!
		2017/03/14	Added AngryGlider enemy based on the Glider enemy to the XML file
		2017/02/25	Added a name variable for Player for use with High Scores table
					fstream added to read in high scores from file to render to screen using loadFromRenderedText() in TextureManager class
		2017/02/16	Added SDL_ttf library to render text in the game
					Pressing the M button in game turns Music On / Off
		2017/02/07	Added game timer function in PlayState, to keep track of the seconds passed since the game / level started

*/
#include "Game.h"
#include <SDL_image.h>
#include <SDL_ttf.h>	// 16/02/2017 Add font
#include "TextureManager.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "Player.h"
#include "ScrollingBackground.h"
#include "SoundManager.h"
#include "RoofTurret.h"
#include "ShotGlider.h"
#include "AngryGlider.h"		// 2017/03/14
#include "Eskeletor.h"
#include "Level1Boss.h"
#include "GameOverState.h"
#include <iostream>

using namespace std;

Game* Game::s_pInstance = 0;

Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_bRunning(false),
m_pGameStateMachine(0),
m_playerLives(3),
m_scrollSpeed(0.8),
m_bLevelComplete(false),
m_bChangingState(false) {
    // add some level files to an array
    m_levelFiles.push_back("assets/map1.tmx");
    m_levelFiles.push_back("assets/map2.tmx");
        
    m_currentLevel = 1;	// start at this level
}

Game::~Game() {
    // we must clean up after ourselves to prevent memory leaks
    m_pRenderer= 0;
    m_pWindow = 0;
}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {    
    // store the game width and height
    m_gameWidth = width;
    m_gameHeight = height;

	if (fullscreen) { windowFlag = SDL_WINDOW_FULLSCREEN; }
	//windowFlag = SDL_WINDOW_FULLSCREEN;	// Sets the game as full screen SDL_WINDOW_SHOWN
	windowFlag = SDL_WINDOW_SHOWN;			// Sets the game as Windowed 
    
    // attempt to initialise SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)  {
        cout << "SDL init success\n";
        // init the window
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, windowFlag);
        
        if(m_pWindow != 0) { // window init success
            cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
            
            if(m_pRenderer != 0) { // renderer init success
                cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 0,0,0,255);
				
				int imgFlags = IMG_INIT_PNG;																	// Initialize PNG loading
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					//success = false;
				}
				//Initialize SDL_ttf
				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					return false;
				}
				
            }
            else {
                cout << "renderer init fail\n";
                return false; // renderer init fail
            }
        }
        else {
            cout << "window init fail\n";
            return false; // window init fail
        }
    }
    else {
        cout << "SDL init fail\n";
        return false; // SDL init fail
    }

    
    // add some sound effects - TODO move to better place
	TheSoundManager::Instance()->load("assets/DST_ElectroRock.ogg", "music1", SOUND_MUSIC);
	TheSoundManager::Instance()->load("OriginalMusic/song1.mp3", "music2", SOUND_MUSIC);			// 2017/03/16 Added song
	TheSoundManager::Instance()->load("OriginalMusic/song2.mp3", "music3", SOUND_MUSIC);			// 2017/03/16 Added song
    TheSoundManager::Instance()->load("assets/boom.wav", "explode", SOUND_SFX);
	TheSoundManager::Instance()->load("assets/phaser.wav", "shoot", SOUND_SFX);
	TheSoundManager::Instance()->load("assetsNew/laser2.wav", "fire", SOUND_SFX);						// 2017/04/21 Added Fire effect for Player weapon

	//TheSoundManager::Instance()->playMusic("music1", -1);
	TheSoundManager::Instance()->playMusic(rand() % 3 + 1);											// 2017/03/16 Play random song
    
    TheInputHandler::Instance()->initialiseJoysticks();												// 2017/04/21 Needs to be uncommented for joystick to initialise
    
    // register the types for the game
    TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    TheGameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
    TheGameObjectFactory::Instance()->registerType("Turret", new TurretCreator());
    TheGameObjectFactory::Instance()->registerType("Glider", new GliderCreator());
	TheGameObjectFactory::Instance()->registerType("ShotGlider", new ShotGliderCreator());
	TheGameObjectFactory::Instance()->registerType("AngryGlider", new AngryGliderCreator());		// 2017/03/14
    TheGameObjectFactory::Instance()->registerType("RoofTurret", new RoofTurretCreator());
    TheGameObjectFactory::Instance()->registerType("Eskeletor", new EskeletorCreator());
    TheGameObjectFactory::Instance()->registerType("Level1Boss", new Level1BossCreator());
    
    // start the menu state
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());

    m_bRunning = true; // everything inited successfully, start the main loop
    return true;
}

void Game::setCurrentLevel(int currentLevel) {
    m_currentLevel = currentLevel;
    m_pGameStateMachine->changeState(new GameOverState());
    m_bLevelComplete = false;
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);
    
	m_pGameStateMachine->render();
	
    SDL_RenderPresent(m_pRenderer);
}

void Game::update(){	
		m_pGameStateMachine->update();
}

void Game::handleEvents() {
	/*
		If button F11 is pressed change the game between Full Screen and Windowed
		This option can also be selected from the settings menu of the game
	
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_F11)) {
		Game::Instance()->fullScreenOrWindowed();
	}
	*/
		TheInputHandler::Instance()->update();
}

void Game::clean() {
    cout << "cleaning game\n";
    
    TheInputHandler::Instance()->clean();
    
    m_pGameStateMachine->clean();
    
    m_pGameStateMachine = 0;
    delete m_pGameStateMachine;
    
    TheTextureManager::Instance()->clearTextureMap();
    
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
	IMG_Quit();
}

/*
	2017/03/23 Function to change between Fullscreen and Windowed view
*/
void Game::fullScreenOrWindowed() {
	if (windowFlag == SDL_WINDOW_FULLSCREEN)
		windowFlag = SDL_WINDOW_SHOWN;
	else
		windowFlag = SDL_WINDOW_FULLSCREEN;

	SDL_SetWindowFullscreen(m_pWindow, windowFlag);
}