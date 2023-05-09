#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), box(5, 5, 30, 30) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
		k->fruitType = 0;//getRandom(0, 3);
        gameKeys.push_back(k);
    }
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

	aniForward->preload();
	aniDownwards->preload();
	aniRight->preload();
	aniLeft->preload();

	aniFStill->preload();
	aniDStill->preload();
	aniLStill->preload();
	aniRStill->preload();

	aniBanana->preload();
	
	//anim = new Animation("Animations/CSV/testAnim.csv");
	//anim->preload();
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

	for (auto key : gameKeys) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 200;
			key->isAlive = false;
			numKeys--;
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
	gfx->setDrawColor(SDL_COLOR_RED);
	//gfx->drawRect(box); //uncomment for debugging

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
		if (key->isAlive)
		{
			gfx->drawCircle(key->pos, 5);
			if (key->fruitType == 0)
			{
				//debug("fruit type is banana");
				//std::cout <<  key->pos.x;
				aniBanana->setXYPos(key->pos.x, key->pos.y, true);
				//aniBanana->render(gfx);
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
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length() * 50, 25);

	if (gameWon)
		gfx->drawText("YOU WON", 250, 500);
}