#pragma once
#include <string>

class frameworkGraphics
{
	public:
		bool fGFX_initialize(void);
		void fGFX_quit(void);

		SDL_Texture* fGFX_loadTexture(std::string path);

		void setRenderer(SDL_Renderer*);
		SDL_Renderer* getRenderer(void);

	//private:
	
};