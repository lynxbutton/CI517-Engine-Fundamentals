#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"
#include "../GraphicsEngine.h"
#include "../ResourceManager.h"

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
	friend class XCube2Engine;
	private:
		std::string animName;
		int x, y, w, h; // rect features
		int frameRate, playBackTime, spritesInRow, spritesInColumn;
		int spX, spY, spW, spH, scW, scH; //sprite locations
		int currFrame = 0;
		int frameNum = 0; // only changed by change sprite funct
		SDL_RendererFlip animFlip;
		//json file vars
		bool jsonFile = false;
		bool run = true;
		std::vector<int> keyFrames;

		//Textures & Graphics
		SDL_Texture* texture;
		SDL_Rect* srcRect;
		SDL_Rect* destRect;
		
		//file locations
		std::string spriteSheetLoc;
		std::string jsonLoc;

		//movement vars
		bool frameStarted = false;
		bool addFrames = false;
		bool pBComplete = false;
		int seconds = 0;
		int frame = 0;
		int mainFJ, subFLeft;
		int timer = 0;

	public:
		Animation();
		Animation(std::string CSVlocation);
		std::vector<std::string> readAnimCSV(std::string fileName);
		void assignCSVContent(std::vector<std::string> content);

		void Animation::preload();
		SDL_Rect* Animation::chooseSprite(int curr);
		int Animation::changeSprite(std::shared_ptr<GraphicsEngine> gfx, int keyframe);
		void Animation::render(std::shared_ptr<GraphicsEngine> gfx);

		void Animation::quit();

		//Getters & Setters
		int getXPos() { return x; };
		void setXPos(int newX) { x = newX; };
		int getYPos() { return y; };
		void setYPos(int newY) { y = newY; };

};

#endif