#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"

struct GameKey {
	Point2 pos;
	bool isAlive;
	int fruitType;
};

class MyGame : public AbstractGame {
	private:
		Rect box;

		Vector2i velocity;

		std::vector<std::shared_ptr<GameKey>> gameKeys;

		/* GAMEPLAY */
		int score, numKeys, lives;
		bool gameWon;

		int facing = 0;
		bool still = true;
		//player character anims
		Animation* aniForward;
		Animation* aniDownwards;
		Animation* aniRight;
		Animation* aniLeft;
		Animation* aniFStill;
		Animation* aniDStill;
		Animation* aniRStill;
		Animation* aniLStill;
		//fruit anims
		Animation* aniBanana;
		Animation* aniGrape;
		Animation* aniOrange;
		Animation* aniStraw;

		SDL_Texture* grassTex;
		SDL_Rect* grassRect;

		int radius = 20;
		Mix_Chunk* splat;
		Mix_Music* bgMusic;

		void handleKeyEvents();
		void update();
		void render();
		void renderUI();
	public:
        MyGame();
		~MyGame();
};

#endif