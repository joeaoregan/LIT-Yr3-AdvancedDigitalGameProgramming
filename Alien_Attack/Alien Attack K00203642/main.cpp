/* 2017-02-03:
Added defines for screen width & height
*/
#include "Game.h"
#include "windows.h"
#include <iostream>

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **argv) {
	srand(static_cast<unsigned int>(time(0)));	// Seed the random number
	//std::cout << "test" << std::endl;

	AllocConsole();
	FILE* myFile;
	freopen_s(&myFile, "CON", "w", stdout);

    Uint32 frameStart, frameTime;
    
    std::cout << "game init attempt...\n";
    if(TheGame::Instance()->init("K00203642 - Alien Attack", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, false))  { // 2017/04/22 Changed to 800 x 510
        std::cout << "game init success!\n";
        while(TheGame::Instance()->running()) {				// Game loop
            frameStart = SDL_GetTicks();
            
            TheGame::Instance()->handleEvents();			// Handle the game events
            TheGame::Instance()->update();					// Update the game objects
            TheGame::Instance()->render();					// Render the game objects
            
            frameTime = SDL_GetTicks() - frameStart;
            
            if(frameTime < DELAY_TIME) {					// Adjust delay time to match up to frame rate
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
        }
    }
    else  {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }
    
    std::cout << "game closing...\n";
    TheGame::Instance()->clean();							// End the game

	system("pause");
    
    return 0;
}
