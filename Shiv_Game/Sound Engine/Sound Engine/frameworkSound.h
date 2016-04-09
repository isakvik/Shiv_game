#pragma once

class frameworkSound
{
public:
	frameworkSound(void);
	~frameworkSound(void);

	int loadSound();

private:
	int endWithError(char* msg);
};

