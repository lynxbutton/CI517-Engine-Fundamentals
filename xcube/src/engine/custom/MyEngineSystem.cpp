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
					if (std::stoi(content[4]) > 0) { spritesInImage = std::stoi(content[4]); }
					else { debug("Sprite amount not compatible."); run = false; }
				}
				catch (const std::invalid_argument& e) { debug("Sprite amount not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Sprite amount out of range."); run = false; }
				break;
			case 5: //Checking for json file - later feature (possibly?)
				try { //catching if nothing is entered into the field
					int locLen = content[5].length();
					if (content[3].substr(locLen - 5, locLen) == ".json")
					{
						jsonLoc = content[5];
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
			case 6: //sprite width
				//Catching if stoi returns any errors & making sure the number is bigger than 0
				try {
					if (std::stoi(content[6]) > 0) { spW = std::stoi(content[6]); }
					else { debug("Sprite width not compatible."); run = false; }
				}
				catch (const std::invalid_argument& e) { debug("Sprite width not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Sprite width not compatible."); run = false; }
				break;
			case 7: //sprite height
				//Catching if stoi returns any errors & making sure the number is bigger than 0
				try {
					if (std::stoi(content[7]) > 0) { spH = std::stoi(content[7]); }
					else { debug("Sprite height not compatible."); run = false; }
				}
				catch (const std::invalid_argument& e) { debug("Sprite height not compatible."); run = false; }
				catch (const std::out_of_range& e) { debug("Sprite height not compatible."); run = false; }
				break;
			default:
				try {//keyframes must be entered from 0
					if (std::stoi(content[i]) < spritesInImage)
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
		/*std::cout << spriteSheetLoc;
		//ensure the image has been loaded and converted correctly
		surface = IMG_Load(spriteSheetLoc.c_str());
		if (surface == NULL || GFX::createTextureFromSurface(surface) == NULL)
		{
			debug("Spritesheet couldn't be loaded. ", SDL_GetError());
			run = false;
		}
		else
		{
			texture = GFX::createTextureFromSurface(surface);
			//std::cout << SDL_GetError();
			SDL_FreeSurface(surface);
			surface = NULL;
		}*/
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
			debug("theres a json?");
		}
		else
		{
			//srcRect = new SDL_Rect{ 0,0,spW,spH };
			//destRect = new SDL_Rect{ 15,15,spW,spH };
			destRect = new SDL_Rect{ 15,15,128,48};
		}

		//check source and dest rects are not NULL
		if (destRect != NULL && texture != NULL && gfx != NULL)
		{
			gfx->drawTexture(texture, destRect);
		}
		else
		{
			debug("Rect is not ok");
			//destRect = new SDL_Rect{ 5,5,10,10 };
		}
	}
}

void Animation::quit()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}