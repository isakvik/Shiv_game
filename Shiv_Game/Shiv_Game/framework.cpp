//All code written by "Dan Kristian", unless stated otherwise.//

/*

Neccessary Documentation:

SDL2:			https://wiki.libsdl.org/FrontPage
SDL2_image:		http://jcatki.no-ip.org:8080/SDL_image/
SDL2_ttf:		http://jcatki.no-ip.org:8080/SDL_ttf/
OpenAL:			https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf

*/


#include "framework.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "al.h"
#include "alc.h"

#include <iostream>
#include <string>

using namespace std;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;

ALCdevice* mainDevice = NULL;
ALCcontext* mainContext = NULL;



bool frameworkInit(){

	bool bInitSuccess = true;

	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
		//Prints error, and file and line it occurred.
		cout << "SDL could not initialize:\n" << SDL_GetError() <<"\nOccured in file and line respectively:\n" << __FILE__ << "\t" << __LINE__ << endl;

		bInitSuccess = false;
	}
	
	else{
		mainWindow = SDL_CreateWindow( "Shiv", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( mainWindow == NULL ){
			cout << "SDL_Window could not initialize:\n" << SDL_GetError() <<"\nOccured in file and line respectively:\n" << __FILE__ << "\t" << __LINE__ << endl; 

			bInitSuccess = false;
		}

		else{
			int flags = IMG_INIT_PNG;
			int initted = IMG_Init(flags);
			if( flags && (initted != flags )){
				cout << "IMG could not initialize:\n" << IMG_GetError() <<"\nOccured in file and line respectively:\n" << __FILE__ << "\t" << __LINE__ << endl; 

				bInitSuccess = false;
			}

			else{
				mainDevice = alcOpenDevice( NULL );

				if( mainDevice == NULL ){
					cout << "OpenAL could not initialize:\n" << alGetError() <<"\nOccured in file and line respectively:\n" << __FILE__ << "\t" << __LINE__ << endl; 

					bInitSuccess = false;
				}

				else{
					mainContext = alcCreateContext( mainDevice, NULL );
					alcMakeContextCurrent( mainContext );
					if( TTF_Init() == -1 ){
						cout << "TTF could not initialize:\n" << TTF_GetError() <<"\nOccured in file and line respectively:\n" << __FILE__ << "\t" << __LINE__ << endl; 

						bInitSuccess = false;
					}
				}
			}
		}
	}
	
	return bInitSuccess;

}

void getRenderer(SDL_Renderer* destination){
	destination = mainRenderer;
};

void frameworkQuit(){
	SDL_DestroyWindow( mainWindow );
	SDL_DestroyRenderer( mainRenderer );

	mainContext = alcGetCurrentContext(); 
	mainDevice = alcGetContextsDevice( mainContext ); 
	alcDestroyContext( mainContext );

	mainWindow = NULL;
	mainRenderer = NULL;
	alcMakeContextCurrent( NULL );

	TTF_Quit();
	alcCloseDevice( mainDevice );
	IMG_Quit();
	SDL_Quit();

}