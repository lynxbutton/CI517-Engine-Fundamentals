#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"
#include "../GraphicsEngine.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class MyEngineSystem {
	friend class XCube2Engine;
	private:

	public:
};

class Animation {
	private:
		std::string animName;
		int x, y, w, h; // rect features
		int frameRate, playBackTime, spritesInImage;
		int spX, spY, spW, spH; //sprite locations
		int currFrame = 0;
		//json file vars
		bool jsonFile = NULL;
		bool run = true;
		std::vector<int> keyFrames;

		//Textures & Graphics
		SDL_Surface* surface;
		SDL_Texture* texture;
		SDL_Rect* rect;
		GraphicsEngine* gfx;
		
		//file locations
		std::string spriteSheetLoc;
		std::string jsonLoc;

	public:
		void testing();
		std::vector<std::string> readAnimCSV(std::string fileName);
		void assignCSVContent(std::vector<std::string> content);
		void Animation::setUpAnim();

		//make a constructor that reads from a given file

		//Getters & Setters
		int getXPos() { return x; };
		void setXPos(int newX) { x = newX; };
		int getYPos() { return y; };
		void setYPos(int newY) { y = newY; };

};

#endif