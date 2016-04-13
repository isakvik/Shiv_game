#pragma once
#include <string>
#include <windows.h>
#include <al.h>
#include <alc.h>

using namespace std;
	
	//Function that sets a listener position	
	void listenerPos();

	//Function that sets a source position
	void sourcePos();
	
	//Function to load sound into object.
	bool loadSound(string urlSound);

	//Function to play sound. 
	bool playSound();