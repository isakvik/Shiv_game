//  Author: Jesper Dahl Ellingsen  //
#include "frameworkSound.h"
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <al.h>
#include <alc.h>
#include <string>

using namespace std;
//------------------------------------------------------------------------------------
							//Varibles in listenerPos();
	//

	
//------------------------------------------------------------------------------------
							//Variables for loadSound();


	//Creates variables to store information about the WAVE file.
	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;

	//Creates variables for sources, buffers and information needed to load them
	ALuint sourceID;												
	ALuint bufferID;											
	ALuint frequency;													
	ALenum format = 0;		

	//Value that will return as true or false, depending of if it fails or not
	bool bLoadSuccess = true;												
//------------------------------------------------------------------------------------	
							//Variables for playSound();


	//Value that will return as true or false, depending of if it fails or not
	bool bPlaySuccess = true;
//------------------------------------------------------------------------------------

bool endWithError(string msg)
{
	cout << msg << endl;
	bLoadSuccess = false;

	return bLoadSuccess;
}



void listenerPos()
{

	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListener3f(AL_ORIENTATION, 0, 0, -1);
}



void sourcePos()
{
	

	alSource3f(sourceID, AL_POSITION, 0, 0, 0);
	alSource3f(sourceID, AL_VELOCITY, 0, 0, 0);
	alSourcei(sourceID, AL_LOOPING, AL_FALSE);
}



bool loadSound(string urlSound)
{

	//Loading the wave file
	FILE *fp = NULL;													//Creates a FILE pointer
	fopen_s(&fp, urlSound.c_str(), "r");								//Opens the WAVE file
	if (fp == NULL)														//Could not open file
	{
		cout << type;
	}



	//Checks if the WAVE file is ok
	fread(type, sizeof(char), 4, fp);									//fread reads the bits of the sound file to find information
	if (!strcmp(type, "RIFF"))											//Checks if the first four bits contains RIFF
	{
		cout << type << "\n";
	}

	fread(&size, sizeof(DWORD), 1, fp);									

	fread(type, sizeof(char), 4, fp);									
	if (!strcmp(type, "WAVE"))											
	{
		cout << type << "\n";
	}

	fread(type, sizeof(char), 4, fp);									
	if (!strcmp(type, "fmt ")) 											
	{	
		cout << type << "\n";
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
		endWithError("Error: Missing Data");
	}

	fread(&dataSize, sizeof(DWORD), 1, fp);		


	//Prints out information for debugging purposes

	cout << "Format Type: " << formatType << "\n";
	cout << "Channels: " << channels << "\n";
	cout << "Sample Rate: " << sampleRate << "\n";
	cout << "Average Bytes Per Second: " << avgBytesPerSec << "\n";
	cout << "Bytes Per Sample: " << bytesPerSample << "\n";
	cout << "Bits Per Sample: " << bitsPerSample << "\n";
	cout << "Data Size: " << dataSize << "\n \n";


	//Creates an array to store the data of the sound file
	unsigned char* data = new unsigned char[dataSize];					//Allocates memory for the sound data
	fread(data, sizeof(BYTE), dataSize, fp);	     					//Reads the sound data
			

	//Generates buffers and sources
	alGenBuffers(1, &bufferID);											
	alGenSources(1, &sourceID);											
	if (sourceID == 0)									
	{
		endWithError("Error: GenSource");
	}

	if (bufferID == 0)									
	{
		endWithError("Error: GenBuffer");
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

	//If there is no format for the WAVE file	
	if (!format)																
	{
		endWithError("Error: Wrong BitPerSample");
	}
		
	ALuint frequency = static_cast <unsigned int> (sampleRate);			//Sets frequency to samplerate					


	//Prints out information for debugging purposes
	cout << "bufferID: " << bufferID << "\n";
	cout << "sourceID: " << sourceID << "\n";
	cout << "format: "<< format << "\n";
	cout << "dataSize: "<< dataSize << "\n";
	cout << "frequency: "<< frequency << "\n";

	alBufferData(bufferID, format, data, dataSize, frequency);			//Stores the sound in the OpenAL buffer
	if (alGetError() != AL_NO_ERROR)										
    {
		endWithError("Error: Loading ALBuffer");
    }

	alSourcei(sourceID, AL_BUFFER, bufferID);							//Connects buffer to source (Sound to object)
	if (alGetError() != AL_NO_ERROR)                                    
    {
		endWithError("Error: Loading ALSource");
	}


	return bLoadSuccess;
}



bool playSound()
{
	 alSourcePlay(sourceID);
	 return bPlaySuccess;
}