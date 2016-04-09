#include "frameworkSound.h"
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <al.h>
#include <alc.h>
#include <string>

using namespace std;

int frameworkSound::endWithError(char* msg)
{
	//Function that displays an error message, then exits the function
	cout << msg << "\n";
	system("PAUSE");
	return 0;
}
using namespace std;

frameworkSound::frameworkSound(void)
{
}  


frameworkSound::~frameworkSound(void)
{
}

//Function that loads a soundfile, into a source
int frameworkSound::loadSound() {

	//Loading the wave file
	FILE *fp = NULL;														//Creates a FILE pointer
	fp = fopen("applause.wav", "rb");										//Opens the WAVE file
	if (fp == NULL)															//Could not open file
	{
		return endWithError("Error: Failed to open file");
	}


	//Creates variables to store information about the WAVE file
	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;


	//Checks if the WAVE file is ok
	fread(type, sizeof(char), 4, fp);									//Reads the first four bits of the WAVE file
	if (!strcmp(type, "RIFF"))											//Checks if the first four bits contains RIFF
	{
		return endWithError("Error: Not a RIFF format");
	}

	fread(&size, sizeof(DWORD), 1, fp);									//Reads the next bit, which contains the size of the WAVE file

	fread(type, sizeof(char), 4, fp);									//Reads the next four bits of the WAVE file
	if (!strcmp(type, "WAVE"))											//Checks if it they contain WAWE
	{
		return endWithError("Error: Not a WAVE format");
	}

	fread(type, sizeof(char), 4, fp);									//Reads the next four bits of the WAVE file
	if (!strcmp(type, "fmt ")) {											//Checks if it they contain "fmt "
			return endWithError("Error: Not a fmt format");
		}

		fread(&chunkSize, sizeof(DWORD), 1, fp);							//Reads the next bit, which contains the chunksize of the WAVE file

		fread(&formatType, sizeof(short), 1, fp);							//Reads the next bit, which contains the formattype of the WAVE file

		fread(&channels, sizeof(short), 1, fp);								//Reads the next bit, which contains the channels of the WAVE file

		fread(&sampleRate, sizeof(DWORD), 1, fp);							//Reads the next bit, which contains the samplerate of the WAVE file

		fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);						//Reads the next bit, which contains the size of the WAVE file	

		fread(&bytesPerSample, sizeof(short), 1, fp);						//Reads the next bit, which contains the size of the WAVE file

		fread(&bitsPerSample, sizeof(short), 1, fp);						//Reads the next bit, which contains the size of the WAVE file

		fread(type, sizeof(char), 4, fp);									//Reads the next four bits, which contains the data of the WAVE file
		if (!strcmp(type, "data"))											//Checks if they contain "data"
		{
			return endWithError("Error: Missing Data");
		}

		fread(&dataSize, sizeof(DWORD), 1, fp);								//Reads the next bit, which contains the datasize of the WAVE file



		unsigned char* buf = new unsigned char[dataSize];					//Allocates memory for the sound data
		fread(buf, sizeof(BYTE), dataSize, fp);								//Reads the sound data



		ALuint source;														//Where the sound comes from	
		ALuint buffer;														//Contains the sound data
		ALuint frequency = sampleRate;										//Samplerate of the WAVE file
		ALenum format = 0;													//Audio format (bits per sample, number of channels)



		alGenBuffers(1, &buffer);											//Generates a OpenAL buffer and a link "buffer"
		alGenSources(1, &source);											//Generates a OpenAL source and link to "source"
		if (alGetError() != AL_NO_ERROR)										//If there is any error during the generating
		{
			return endWithError("Error: GenSource");
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

		if (!format)															//If there is no format for the WAVE file
			return endWithError("Error: Wrong BitPerSample");



		alBufferData(buffer, format, buf, dataSize, frequency);				//Stores the sound in the OpenAL buffer
		if (alGetError() != AL_NO_ERROR)										//If there is an error loading the buffer
			return endWithError("Error: Loading ALBuffer");

		alSourcei(source, AL_BUFFER, buffer);								//Connects buffer to source (Sound to object)
		if (alGetError() != AL_NO_ERROR)										//If there is an error loading the source
			return endWithError("Error: Loading ALSource");


		fclose(fp);															//Closes the WAVE file
		delete[] buf;														//Deletes sound data buffer
		alDeleteSources(1, &source);										//Deletes the OpenAL source
		alDeleteBuffers(1, &buffer);										//Deletes the OpenAL bufer
		
	return EXIT_SUCCESS;
}