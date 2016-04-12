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
	//Creates variable to store format type
	ALenum format = 0;														
	
	//Values that will return as true or false, depending of if it fails or not
	bool bLoadSuccess = true;												
	bool bPlaySuccess = true;
}  


frameworkSound::~frameworkSound(void)
{
}

bool frameworkSound::endWithError(string msg)
{
	cout << msg << endl;
	bLoadSuccess = false;

	return bLoadSuccess;
}

//Function that loads a soundfile, into a source
bool frameworkSound::loadSound(string urlSound) {

	//Loading the wave file
	FILE *fp = NULL;													//Creates a FILE pointer
	fopen_s(&fp, urlSound.c_str(), "r");								//Opens the WAVE file
	if (fp == NULL)														//Could not open file
	{
		endWithError("Error: Not a RIFF format");
	}



	//Checks if the WAVE file is ok
	fread(type, sizeof(char), 4, fp);									//fread reads the bits of the sound file to find information
	if (!strcmp(type, "RIFF"))											//Checks if the first four bits contains RIFF
	{
		endWithError("Error: Not a RIFF format");
	}

	fread(&size, sizeof(DWORD), 1, fp);									

	fread(type, sizeof(char), 4, fp);									
	if (!strcmp(type, "WAVE"))											
	{
		endWithError("Error: Not a WAVE format");
	}

	fread(type, sizeof(char), 4, fp);									
	if (!strcmp(type, "fmt ")) 											
	{	
		endWithError("Error: Not a fmt format");
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
		cout << "Chunk Size: " << chunkSize << "\n";
		cout << "Format Type: " << formatType << "\n";
		cout << "Channels: " << channels << "\n";
		cout << "Sample Rate: " << sampleRate << "\n";
		cout << "Average Bytes Per Second: " << avgBytesPerSec << "\n";
		cout << "Bytes Per Sample: " << bytesPerSample << "\n";
		cout << "Bits Per Sample: " << bitsPerSample << "\n";
		cout << "Data Size: " << dataSize << "\n";


		//Creates an array to store the data of the sound file
		unsigned char* data = new unsigned char[dataSize];					//Allocates memory for the sound data
		fread(data, sizeof(BYTE), dataSize, fp);	     					//Reads the sound data
			

		//Generates buffers and sources
		alGenBuffers(1, &bufferID);											
		alGenSources(1, &sourceID);											
		if (alGetError() != AL_NO_ERROR)									
		{
			endWithError("Error: GenSource");
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

bool frameworkSound::playSound()
{
	 alSourcePlay(sourceID);
	 return bPlaySuccess;
}