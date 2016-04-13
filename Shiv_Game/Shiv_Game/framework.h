#pragma once
#include <SDL.h>

//Initializes SDL, SDL_image, OpenAL, SDL_ttf. 
bool frameworkInit();

//Gets renderer
SDL_Renderer* getRenderer(void);
void setRenderer(SDL_Renderer*);

//Quits SDL, SDL_image, OpenAL, SDL_ttf. 
void frameworkQuit();

