#include "MyEngineSystem.h"

void Animation::testing()
{
	debug("Animation Test Complete");
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
				debug("Uneeded row in animation CSV file."); // add what anim it is maybe?
			}
		}
	}
	else
		debug("Could not open the file");

	return row;
}

void Animation::assignCSVContent(std::vector<std::string> content)
{
	for (int i = 0; i < content.size(); i++)
	{
		//Order may be changed in the future
		//DO ERROR CHECKING
		std::cout << content[i] << " ";
		switch (i) // These values will always be first despite animation size
		{
		case 0:
			animName = content[0];
			/*case 1:
			try {
				frameRate = std::stoi(content[1]);
				throw(content[1]);
			}
			catch (std::string err1) { debug("Frame rate not compatible"); }
		case 2:
			try {
				playBackTime = std::stoi(content[2]);
				throw(content[2]);
			}
			catch (std::string err2) { debug("Playback time not compatible"); }
		case 3:
			spriteSheetLoc = content[3]; //make sure it ends w a suitable file extension!
		case 4:
			//sprite amount within image
		case 5:
			//sprite width
		case 6:
			//sprite height*/
		}
	}
	std::cout << "\n";
}

void Animation::setUpAnim()
{

}