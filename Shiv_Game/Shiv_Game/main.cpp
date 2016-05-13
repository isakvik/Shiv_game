#include "framework.h"
#include "frameworkGraphics.h"
#include <iostream>

using namespace std;

SDL_Event e;
bool quit = false;

int main( int argc, char* args[] ){
	
	frameworkGraphics obj_1;

	cout << obj_1.fGFX_initialize() << endl;
	
	SDL_Rect source = {0,0,45,90};
	SDL_Rect source2 = {45,0,45,90};
	SDL_Rect dest = {100,100,100,100};
	SDL_Rect dest2 = {200,100,100,100};

	SDL_RenderClear( obj_1.getRenderer() );
	SDL_RenderCopy( obj_1.getRenderer() , obj_1.fGFX_loadTexture("test.png"), &source, &dest);
	SDL_RenderCopy( obj_1.getRenderer() , obj_1.fGFX_loadTexture("test.png"), &source2, &dest2);
	SDL_RenderPresent( obj_1.getRenderer() );

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

	obj_1.fGFX_quit();

	return 0;
}