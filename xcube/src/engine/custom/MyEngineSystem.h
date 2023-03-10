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
		int x, y, w, h;
		int frameRate, playBackTime;
		int currFrame = 0;
		bool run = true;
		//int keyFrames[playBackTime]; //array?
		// sprite sheet
		// amount of frames in spritesheet
		//int spriteFrames;

		//Textures & Graphics
		SDL_Surface* surface;
		SDL_Texture* texture;
		SDL_Rect* rect;
		GraphicsEngine* gfx;
		
		//file locations
		std::string spriteSheetLoc;
		std::fstream file;

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