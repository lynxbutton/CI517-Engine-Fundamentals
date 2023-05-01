#include "MyEngineSystem.h"

Animation::Animation()
{
	debug("Empty Animation file created.");
}

Animation::Animation(std::string CSVlocation)
{
	assignCSVContent(readAnimCSV(CSVlocation));
}

//Will read given CSV file and return its contents in an array (string)
std::vector<std::string> Animation::readAnimCSV(std::string fileName)
{
	std::fstream file(fileName, std::ios::in);

	std::vector<std::string> row; // array (string)
	std::string line, word;

	if (file.is_open())
	{
		int max = 0;
		while (getline(file, line))
		{
			if (max < 1)
			{
				row.clear();

				std::stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				max += 1;
			}
			else
			{
				debug("Uneeded row in animation CSV file.");
				run = false;
			}
		}
	}
	else
	{
		debug("Could not open the file"); 
		run = false;
	}

	file.close();

	return row;
}

//error checks content and assigns to the correct variables within the class
void Animation::assignCSVContent(std::vector<std::string> content)
{
	for (int i = 0; i < content.size(); i++)
	{
		if (run == true) //if animation information can be used
		{
			switch (i) // These values will always be first despite animation size
			{
			case 0:
				animName = content[0];
				break;
			case 1:
				//Catching if stoi returns any errors.
				try { //Make sure it's bigger than zero
					if (std::stoi(content[1]) > 0) { frameRate = std::stoi(content[1]);}
					else { debug("Frame rate not compatible."); run = false;}
				}
				catch (const std::invalid_argument& e) { debug("Frame rate not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Frame rate out of range."); run = false; }
				break;
			case 2:
				//Catching if stoi returns any errors.
				try {
					if (std::stoi(content[2]) > 0) { playBackTime = std::stoi(content[2]); }
					else { debug("Playback time not compatible."); run = false; }
				}
				catch (const std::invalid_argument& e) { debug("Playback time not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Playback time out of range."); run = false; }
				break;
			case 3:
				try { //catching if nothing is entered into the field
					int locLen = content[3].length();
					if (content[3].substr(locLen - 4, locLen) == ".png" || content[3].substr(locLen - 4, locLen) == ".jpg")
					{ 
						spriteSheetLoc = content[3];
					} //make sure it ends w a suitable file extension!
					else
					{ debug("Animation location is invalid."); run = false;}
				}
				catch (const std::invalid_argument& e) { debug("Animation location is invalid."); run = false; }
				catch (const std::out_of_range& e) { debug("Animation location is invalid."); run = false; }
				break;
			case 4://sprite amount within image
				//Catching if stoi returns any errors & making sure the number is bigger than 0
				try { 
					if (std::stoi(content[4]) > 0) { spritesInRow = std::stoi(content[4]); }
					else { debug("Sprite row amount not compatible."); run = false; }
				}
				catch (const std::invalid_argument& e) { debug("Sprite row amount not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Sprite row amount out of range."); run = false; }
				break;
			case 5://sprite amount within image
				//Catching if stoi returns any errors & making sure the number is bigger than 0
				try {
					if (std::stoi(content[5]) > 0) { spritesInColumn = std::stoi(content[5]); }
					else { debug("Sprite column amount not compatible."); run = false; }
				}
				catch (const std::invalid_argument& e) { debug("Sprite column amount not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Sprite column amount out of range."); run = false; }
				break;
			case 6: //Checking for json file - later feature (possibly?)
				try { //catching if nothing is entered into the field
					int locLen = content[6].length();
					if (content[6].substr(locLen - 5, locLen) == ".json")
					{
						jsonLoc = content[6];
						jsonFile = true;
						debug("Animation JSON file found.");
					} //make sure it ends w a suitable file extension!
					else
					{
						debug("Animation lacks JSON file.");
						jsonFile = false;
					}
				}
				catch (const std::invalid_argument& e) { debug("Animation lacks JSON file."); }
				catch (const std::out_of_range& e) { debug("Animation lacks JSON file."); }
				break;
			case 7: //sprite width
				//Catching if stoi returns any errors & making sure the number is bigger than 0
				try {
					if (std::stoi(content[7]) > 0) { spW = std::stoi(content[7]); }
					else { debug("Sprite width not compatible."); run = false; }
				}
				catch (const std::invalid_argument& e) { debug("Sprite width not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Sprite width not compatible."); run = false; }
				break;
			case 8: //sprite height
				//Catching if stoi returns any errors & making sure the number is bigger than 0
				try {
					if (std::stoi(content[8]) > 0) { spH = std::stoi(content[8]); }
					else { debug("Sprite height not compatible."); run = false; }
				}
				catch (const std::invalid_argument& e) { debug("Sprite height not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Sprite height not compatible."); run = false; }
				break;
			case 9: // scale sprite width
				//Catching if stoi returns any errors & making sure the number is bigger than 0
				try {
					if (std::stoi(content[9]) > 0) { scW = std::stoi(content[9]); }
					else { debug("Scale width not compatible."); run = false; }
				}
				catch (const std::invalid_argument& e) { debug("Scale width not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Scale width not compatible."); run = false; }
				break;
			case 10: //scale sprite height
				//Catching if stoi returns any errors & making sure the number is bigger than 0
				try {
					if (std::stoi(content[10]) > 0) { scH = std::stoi(content[10]); }
					else { debug("Scale height not compatible."); run = false; }
				}
				catch (const std::invalid_argument& e) { debug("Scale height not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Scale height not compatible."); run = false; }
				break;
			case 11: //Will the animation be flipped
				try { //catching if nothing is entered into the field
					int locLen = content[11].length();
					if (locLen > 0)
					{
						if (content[11] == "horizontal" || content[11] == "x")
						{
							animFlip = SDL_FLIP_HORIZONTAL;
							debug("Animation will be flipped horizontally.");
						}
						else if (content[11] == "vertical" || content[11] == "y")
						{
							animFlip = SDL_FLIP_VERTICAL;
							debug("Animation will be flipped vertically.");
						}
						else
						{
							animFlip = SDL_FLIP_NONE;
							debug("Animation will be not be flipped.");
						}
					}
					else
					{
						debug("Animation lacks JSON file.");
						jsonFile = false;
					}
				}
				catch (const std::invalid_argument& e) { debug("Animation lacks JSON file."); }
				catch (const std::out_of_range& e) { debug("Animation lacks JSON file."); }
				break;
			default:
				try {//keyframes must be entered from 0
					if (std::stoi(content[i]) < spritesInRow * spritesInColumn)
					{//ensure the sprite will be able to be accessed
						keyFrames.push_back(std::stoi(content[i]));
					}
					else
					{
						debug("Keyframe out of range."); 
						run = false;
					}
				}
				catch (const std::invalid_argument& e) { debug("Keyframe not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Keyframe out of range."); run = false; }
				break;
			}
		}
		else
		{
			debug("Animation cannot be loaded");
			break;
		}
	}
	//ensure that the correct amount of keyframes has been given
	if (keyFrames.size() != playBackTime)
	{
		if (keyFrames.size() > playBackTime)
		{
			debug("Less keyframes required for playback.");
		}
		else debug("More keyframes required for playback.");
		run = false;
	}
}

void Animation::preload() // change to just preload json
{
	if (run) //if an error hasn't already occured
	{
		//preload function will split into two if theres a json file
		if (jsonFile)
		{
			//act for json file.
			debug("theres a json?");
		}
		else
		{
			debug("Sprites will be rendered without JSON file.");
		}
		
		texture = ResourceManager::loadTexture(spriteSheetLoc, SDL_COLOR_WHITE);
		if (texture == nullptr)
		{
			debug("Texture is null and cannot be loaded.");
			run = false;
		}
	}
}

void Animation::render(std::shared_ptr<GraphicsEngine> gfx)
{
	if (run)
	{
		//set source and dest rects
		if (jsonFile)
		{
			//act for json file.
			debug("JSON feature to be added.");
			run = false; //to be removed w json functionality
		}
		else
		{
			frameNum = changeSprite(gfx, frameNum);
			//std::cout << "frame number: " << frameNum;
			currFrame = keyFrames[frameNum];
			//std::cout << "curr frame: " << currFrame;
			srcRect = chooseSprite(currFrame);
			destRect = new SDL_Rect{ 0,0,spW * scW,spH * scH }; // this will change if the character moves!
		}
		//check source and dest rects are not NULL
		if (destRect != NULL && gfx != NULL)
		{
			gfx->drawTexture(texture, srcRect, destRect, 0.0, 0, animFlip);
		}
		else
		{
			debug("Rect or Graphics Engine cannot be accessed.");
			run = false;
		}
	}
}

int Animation::changeSprite(std::shared_ptr<GraphicsEngine> gfx, int keyframe)
{
	if (run)
	{
		if (SDL_GetTicks() > 2800) // 2.8 second grace period after loading
		{
			//debug("Within Animation grace period.");

			if (seconds * keyframe + 1 < playBackTime)
			{
				// check fps and limit the animation to the fps of the game
				int currFR = gfx->getAverageFPS();
				if (currFR < frameRate)
				{
					//if FPS drops too low, pause the animation - also pauses before window loads
					debug("Animation frame rate is higher than average FPS.");
					return keyframe;
				}
				else
				{
					if (frame < frameRate)
					{
						// set up the needed variables to render frames
						if (frameStarted == false)
						{
							//debug("frames reset");
							//std::cout << currFR;
							frameStarted = true;
							addFrames = false;
							mainFJ = currFR / frameRate;
							subFLeft = currFR - (mainFJ * frameRate);
						}

						if (addFrames == false || subFLeft == 0)
						{
							// render current for the normal amount of frames
							if (timer == mainFJ && subFLeft != 0)
							{
								//debug("next keyframe");
								frame += 1;
								addFrames = true;
								timer = 0;
								return keyframe + 1;
							}
							else if (timer == mainFJ && subFLeft == 0)
							{
								//debug("next keyframe");
								frame += 1;
								timer = 0;
								return keyframe + 1;
							}
							else
							{
								//debug("curr keyframe");
								timer += 1;
								return keyframe;
							}
						}
						else
						{
							// render current for added amount of frames
							if (timer == mainFJ + 1 && subFLeft != 0)
							{
								//debug("next keyframe 3");
								addFrames = false;
								frame += 1;
								subFLeft -= 1;
								timer = 0;
								return keyframe + 1;
							}
							else
							{
								//debug("curr keyframe");
								timer += 1;
								return keyframe;
							}
						}
					}
					else
					{
						//debug("second added");
						seconds += 1;
						frame = 0;
						frameStarted = false;
						return seconds * frameRate - 1;
					}
				}
			}
			else
			{
				if (pBComplete == false)
				{
					debug("Playback is completed.");
					pBComplete = true;
				}
				return keyframe;
			}
		}
		else
		{
			return keyframe;
		}
	}
	debug("Keyframe change sprite error.");
	run = false;
	return 0;
}

SDL_Rect* Animation::chooseSprite(int curr)
{
	if (curr > spritesInRow * spritesInColumn - 1 || curr < 0) //checking the overall keyframe is accessible
	{
		debug("Keyframe is out of range.");
		run = false;
		return nullptr;
	}
	else
	{
		int currX = 0; int currY = 0; int loopFrame = 0;
		for (int col = 0; col < spritesInColumn; col++)
		{
			if (loopFrame != curr)
			{
				for (int row = 0; row < spritesInRow - 1; row++)
				{
					if (loopFrame != curr)
					{
						currX += spW;
						loopFrame += 1;
					}
				}
				if (loopFrame != curr)
				{
					currY += spH;
					loopFrame += 1;
					currX = 0;
				}
			}
		}
		SDL_Rect* rect = new SDL_Rect{ currX,currY,spW,spH }; // first two times keyframe to get sprite
		return rect;
	}
}

void Animation::quit()
{
	SDL_DestroyTexture(texture);
}