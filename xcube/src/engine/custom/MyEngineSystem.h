#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"

class MyEngineSystem {
	friend class XCube2Engine;
	private:

	public:
};

class Animation {
	private:
		int x, y, w, h;
		int frameRate, playBackTime;
		int keyFrames; //array?
		// sprite sheet
		// amount of frames in spritesheet
		//anim start time?
		int currFrame;
		//csv file to read and write from?

	public:
		void testing();

		//make a constructor that reads from a given file

		//Getters & Setters
		int getXPos() { return x; };
		void setXPos(int newX) { x = newX; };
		int getYPos() { return y; };
		void setYPos(int newY) { y = newY; };

};

#endif