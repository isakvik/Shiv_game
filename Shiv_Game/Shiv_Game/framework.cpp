//All code written by "Dan Kristian", unless stated otherwise.//

/*

Neccessary Documentation:

SDL2:			https://wiki.libsdl.org/FrontPage
SDL2_image:		http://jcatki.no-ip.org:8080/SDL_image/
SDL2_ttf:		http://jcatki.no-ip.org:8080/SDL_ttf/
OpenAL:			https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf

*/


#include "framework.h"
#include "al.h"
#include "alc.h"

#include <iostream>
#include <string>

using namespace std;

ALCdevice* mainDevice = NULL;
ALCcontext* mainContext = NULL;



bool frameworkInit(){

	bool bInitSuccess = true;
	mainDevice = alcOpenDevice( NULL );

	if( mainDevice == NULL ){
		cout << "OpenAL could not initialize: " << alGetError() <<"\nOccured in file and line respectively: " << __FILE__ << "\t" << __LINE__ << endl; 

		bInitSuccess = false;
	}

	return bInitSuccess;
}

void frameworkQuit(){

	mainContext = alcGetCurrentContext(); 
	mainDevice = alcGetContextsDevice( mainContext ); 

	alcDestroyContext( mainContext );
	alcMakeContextCurrent( NULL );

	alcCloseDevice( mainDevice );

}