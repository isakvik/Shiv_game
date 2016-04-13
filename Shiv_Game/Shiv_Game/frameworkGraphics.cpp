//  Author: Isak Vik  //

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_ttf.h"
#include <iostream>

#include "framework.h"
#include "frameworkGraphics.h"

using namespace std;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;

// load functions

bool frameworkGraphics::fGFX_initialize(void)
{
	bool bInitSuccess = true;

	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
		//prints error, and file and line it occurred.
		cout << "[Error] SDL could not initialize:\n" << SDL_GetError() <<"\nOccured in file and line respectively:\n" << __FILE__ << "\t" << __LINE__ << endl;

		bInitSuccess = false;
	}
	else
	{
		//open window
		mainWindow = SDL_CreateWindow( "Shiv", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( mainWindow == NULL ){
			cout << "[Error] SDL_Window could not initialize: " << SDL_GetError() << " - Occured in file and line respectively: (" << __FILE__ << "," << __LINE__ << ")" << endl; 

			bInitSuccess = false;
		}
		else
        {
            //create renderer for window
            mainRenderer = SDL_CreateRenderer( mainWindow, -1, SDL_RENDERER_ACCELERATED );
            if( mainRenderer == NULL )
            {
                cout << "[Error] Renderer could not be created! SDL Error: " << SDL_GetError() << " - Occured in file and line respectively: (" << __FILE__ << "," << __LINE__ << ")" << endl; 
                bInitSuccess = false;
            }
			else 
			{
				//set bg color
				SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 1);
				SDL_RenderClear(mainRenderer);

				//init image handling
				int flags = IMG_INIT_PNG;
				int initted = IMG_Init(flags);
				if( flags && (initted != flags )){
					cout << "[Error] IMG could not initialize: " << IMG_GetError() << " - Occured in file and line respectively: (" << __FILE__ << "," << __LINE__ << ")" << endl; 
					bInitSuccess = false;
				}
				else 
				{
					//init ttf handling
					if( TTF_Init() == -1 ){
						cout << "[Error] TTF could not initialize: " << TTF_GetError() << " - Occured in file and line respectively: (" << __FILE__ << "," << __LINE__ << ")" << endl; 

						bInitSuccess = false;
					}
				}
			}
		}
	}
	
	return bInitSuccess;
}

SDL_Texture* frameworkGraphics::fGFX_loadTexture( string path )
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        cout << "[Error] Could not load image " << path.c_str() <<"! SDL_image Error: " << IMG_GetError() << endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(mainRenderer, loadedSurface );
        if( newTexture == NULL )
        {
			cout << "[Error] Unable to create texture from " << path.c_str() <<"! SDL Error: " << IMG_GetError() << endl;
        }

        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

SDL_Renderer* frameworkGraphics::getRenderer(void){
	return mainRenderer;
};

void frameworkGraphics::setRenderer(SDL_Renderer* destination){
	destination = mainRenderer;
};

void frameworkGraphics::fGFX_quit(void)
{
	SDL_DestroyWindow( mainWindow );	//destroy all evidence
	SDL_DestroyRenderer( mainRenderer );
	
	mainWindow = NULL;					//free pointers
	mainRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}