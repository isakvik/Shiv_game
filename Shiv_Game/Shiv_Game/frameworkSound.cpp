#include "frameworkSound.h"
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <al.h>
#include <alc.h>
#include <string>
#include <stdio.h>
using namespace std;

frameworkSound::frameworkSound(void)
{
	
	//Creates variables to store information needed to load sound to...
	//Buffers and sources
	ALuint frequency = sampleRate;											//Samplerate of the WAVE file
	ALenum format = 0;														//Audio format (bits per sample, number of channels)
	
	bool bLoadSuccess = true;												//Creates a variable that will return to tell if the code succeded or not
	bool bPlaySuccess = true;
}  


frameworkSound::~frameworkSound(void)
{
}

//Function that loads a soundfile, into a source
bool frameworkSound::loadSound(string urlSound) {

	//Loading the wave file
	FILE *fp = NULL;														//Creates a FILE pointer
	fopen_s(&fp, urlSound.c_str(), "r");									//Opens the WAVE file
	if (fp == NULL)															//Could not open file
	{
		cout << "Error: Not a RIFF format" << endl;
		bLoadSuccess = false;

		return bLoadSuccess;
	}



	//Checks if the WAVE file is ok
	fread(type, sizeof(char), 4, fp);									//fread reads the bits of the sound file to find information
	if (!strcmp(type, "RIFF"))											//Checks if the first four bits contains RIFF
	{
		cout << "Error: Not a RIFF format" << endl;
		bLoadSuccess = false;

		return bLoadSuccess;
	}

	fread(&size, sizeof(DWORD), 1, fp);									

	fread(type, sizeof(char), 4, fp);									
	if (!strcmp(type, "WAVE"))											
	{
		cout << "Error: Not a WAVE format" << endl;
		bLoadSuccess = false;

		return bLoadSuccess;
	}

	fread(type, sizeof(char), 4, fp);									
	if (!strcmp(type, "fmt ")) 											
	{	
		cout << "Error: Not a fmt format" << endl;
		bLoadSuccess = false;

		return bLoadSuccess;
	}

		fread(&chunkSize, sizeof(DWORD), 1, fp);							

		fread(&formatType, sizeof(short), 1, fp);							

		fread(&channels, sizeof(short), 1, fp);								

		fread(&sampleRate, sizeof(DWORD), 1, fp);							

		fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);							

		fread(&bytesPerSample, sizeof(short), 1, fp);						

		fread(&bitsPerSample, sizeof(short), 1, fp);						

		fread(type, sizeof(char), 4, fp);									
		if (!strcmp(type, "data"))											
		{
			cout << "Error: Missing Data" << endl;
			bLoadSuccess = false;

			return bLoadSuccess;
		}

		fread(&dataSize, sizeof(DWORD), 1, fp);								



		unsigned char* buf = new unsigned char[dataSize];					//Allocates memory for the sound data
		fread(buf, sizeof(BYTE), dataSize, fp);								//Reads the sound data



		alGenBuffers(1, &buffer);											//Generates a OpenAL buffer and a link "buffer"
		alGenSources(1, &source);											//Generates a OpenAL source and link to "source"
		if (alGetError() != AL_NO_ERROR)										//If there is any error during the generating
		{
			cout << "Error: GenSource" << endl;
			bLoadSuccess = false;

			return bLoadSuccess;
		}


		//Picks format, accordingly
		if (bitsPerSample == 8)
		{
			if (channels == 1)
				format = AL_FORMAT_MONO8;
			else if (channels == 2)
				format = AL_FORMAT_STEREO8;
		}
		else if (bitsPerSample == 16)
		{
			if (channels == 1)
				format = AL_FORMAT_MONO16;
			else if (channels == 2)
				format = AL_FORMAT_STEREO16;
		}

		if (!format)														//If there is no format for the WAVE file			
		{
		
			cout << "Error: Wrong BitPerSample" << endl;
			bLoadSuccess = false;

			return bLoadSuccess;
		}


		alBufferData(buffer, format, buf, dataSize, frequency);				//Stores the sound in the OpenAL buffer
		if (alGetError() != AL_NO_ERROR)									//If there is an error loading the buffer
		{	
			cout << "Error: Loading ALBuffer" << endl;
			bLoadSuccess = false;

			return bLoadSuccess;
		}
		alSourcei(source, AL_BUFFER, buffer);								//Connects buffer to source (Sound to object)
		if (alGetError() != AL_NO_ERROR)									//If there is an error loading the source
		{	
			cout << "Error: Loading ALSource" <<  endl;
			bLoadSuccess = false;

			return bLoadSuccess;
		}

												//Deletes the OpenAL buffer
		
	return bLoadSuccess;
}

bool frameworkSound::playSound()
{
	 alSourcePlay(source);
	 return bPlaySuccess;
}