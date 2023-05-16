#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), box(5, 5, 30, 30) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	gfx->useFont(font);
	gfx->setWindowTitle("CI517 - Lynx Button's XCube2D Animation System."); //Easter eggs
	gfx->setVerticalSync(true);

    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
		k->fruitType = getRandom(0, 4);
        gameKeys.push_back(k);
    }
	grassTex = ResourceManager::loadTexture("Sprites/grass.png", SDL_COLOR_GRAY);
	grassRect = new SDL_Rect{ 0,0,800,600 };
	splat = ResourceManager::loadSound("SFX/squash.wav");
	bgMusic = ResourceManager::loadMP3("SFX/bgDrums.mp3");
	sfx->playMP3(bgMusic, -1);
	//ANIMATION STARTING FUNCTS ---------------------------------------------------------------------------------
	aniForward = new Animation("Animations/CSV/hero/heroForward.csv");
	aniDownwards = new Animation("Animations/CSV/hero/heroDownward.csv");
	aniRight = new Animation("Animations/CSV/hero/heroRight.csv");
	aniLeft = new Animation("Animations/CSV/hero/heroLeft.csv");

	aniFStill = new Animation("Animations/CSV/hero/heroForwardStill.csv");
	aniDStill = new Animation("Animations/CSV/hero/heroDownStill.csv");
	aniLStill = new Animation("Animations/CSV/hero/heroLeftStill.csv");
	aniRStill = new Animation("Animations/CSV/hero/heroRightStill.csv");

	aniBanana = new Animation("Animations/CSV/fruit/bananaAlive.csv");
	aniGrape = new Animation("Animations/CSV/fruit/grapeAlive.csv");
	aniOrange = new Animation("Animations/CSV/fruit/orangeAlive.csv");
	aniStraw = new Animation("Animations/CSV/fruit/strawberryAlive.csv");

	aniForward->preload();
	aniDownwards->preload();
	aniRight->preload();
	aniLeft->preload();

	aniFStill->preload();
	aniDStill->preload();
	aniLStill->preload();
	aniRStill->preload();

	aniBanana->preload();
	aniGrape->preload();
	aniOrange->preload();
	aniStraw->preload();
}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
		facing = 2;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
		facing = 0;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
		facing = 1;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
		facing = 3;
	}
}

void MyGame::update() {
	if (velocity.x == 0 && velocity.y == 0)
	{
		still = true;
	}
	else
	{
		still = false;
	}

	box.x += velocity.x;
	box.y += velocity.y;

	for (auto key : gameKeys) { // have it check it is within the box
		bool within = false;
		if(key->isAlive)
		{
			Point2 topLeft = Point2(key->pos.x - radius, key->pos.y - radius); Point2 topRight = Point2(key->pos.x + radius, key->pos.y - radius);
			Point2 bottomLeft = Point2(key->pos.x - radius, key->pos.y + radius); Point2 bottomRight = Point2(key->pos.x + radius, key->pos.y + radius);
			if (box.contains(topLeft) || box.contains(topRight) || box.contains(bottomLeft) || box.contains(bottomRight))
			{
				within = true;
			}
		}
		if (within)
		{
			score += 200;
			key->isAlive = false;
			numKeys--;
			sfx->playSound(splat);
			within = false;
		}
	}

	velocity.x = 0;
    velocity.y = 0;

	if (numKeys == 0) {
		gameWon = true;
	}

	//update animation x & y to the box
	aniForward->setXYPos(box.x,box.y, true);
	aniDownwards->setXYPos(box.x, box.y, true);
	aniRight->setXYPos(box.x, box.y, true);
	aniLeft->setXYPos(box.x, box.y, true);

	aniFStill->setXYPos(box.x, box.y, true);
	aniDStill->setXYPos(box.x, box.y, true);
	aniLStill->setXYPos(box.x, box.y, true);
	aniRStill->setXYPos(box.x, box.y, true);

}

void MyGame::render() {
	gfx->drawTexture(grassTex, grassRect, SDL_FLIP_NONE);
	//gfx->setDrawColor(SDL_COLOR_RED);
	//gfx->drawRect(box); //uncomment for debugging

	//gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
		if (key->isAlive)
		{
			//gfx->drawCircle(key->pos, 5); //uncomment for debugging
			if (key->fruitType == 0)
			{
				aniBanana->setXYPos(key->pos.x, key->pos.y, true);
				aniBanana->render(gfx);
			}
			else if (key->fruitType == 1)
			{
				aniGrape->setXYPos(key->pos.x, key->pos.y, true);
				aniGrape->render(gfx);
			}
			else if (key->fruitType == 2)
			{
				aniStraw->setXYPos(key->pos.x, key->pos.y, true);
				aniStraw->render(gfx);
			}
			else if (key->fruitType == 3)
			{
				aniOrange->setXYPos(key->pos.x, key->pos.y, true);
				aniOrange->render(gfx);
			}
		}

	//PLACE FOR ANIMATION RENDERING -------------------------------------------------------------------------------
	if (!still)
	{
		if (facing == 1)
		{
			aniLeft->render(gfx);
		}
		else if (facing == 2)
		{
			aniForward->render(gfx);
		}
		else if (facing == 3)
		{
			aniRight->render(gfx);
		}
		else
		{
			aniDownwards->render(gfx);
		}
	}
	else
	{
		if (facing == 1)
		{
			aniLStill->render(gfx);
		}
		else if (facing == 2)
		{
			aniFStill->render(gfx);
		}
		else if (facing == 3)
		{
			aniRStill->render(gfx);
		}
		else
		{
			aniDStill->render(gfx);
		}
	}
}

void MyGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_GREEN);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length() * 50, 25);

	if (gameWon)
		gfx->drawText("YOU WON", 250, 500);
}