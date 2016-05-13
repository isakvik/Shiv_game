#include "framework.h"
#include <iostream>
#include "frameworkSound.h"
#include "SDL.h"

using namespace std;

int main( int argc, char* args[] ){

    cout << frameworkInit() << endl;

    bool quit = false;
    SDL_Event e;

	loadSound("D:\\GitHub\\Shiv_game\\Shiv_Game\\Shiv_Game\\test.wav");
	playSound();
    //While application is running
    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {	
			
			
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
    }

    frameworkQuit();

    return 0;
}

