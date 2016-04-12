#pragma once
#include <string>
#include <windows.h>
#include <al.h>
#include <alc.h>

using namespace std;

class frameworkSound
{
public:
	//Constructor
	frameworkSound(void);
	
	//Deconstructor
	~frameworkSound(void);

	bool endWithError(string msg);
	
	//Function to load sound into object
	bool loadSound(string urlSound);

	//Function to play sound 
	bool playSound();

private:
	
	//Creates variables to store information about the WAVE file
	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;

	//Creates variables for sources and buffers
	ALuint sourceID;												
	ALuint bufferID;											
	
	//Look in constructor for information
	ALuint frequency;													
	ALenum format;

	bool bLoadSuccess;
	bool bPlaySuccess;
};

