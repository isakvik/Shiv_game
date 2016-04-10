#pragma once
#include <string>
#include <windows.h>
#include <al.h>
#include <alc.h>

using namespace std;

class frameworkSound
{
public:
	frameworkSound(void);
	~frameworkSound(void);

	bool loadSound(string urlSound);

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
	ALuint source;											//Where the sound comes from	
	ALuint buffer;											//Contains the sound data
	
	//Look in constructor for information
	ALuint frequency;													
	ALenum format;

	bool bLoadSuccess;
	bool bPlaySuccess;
};

