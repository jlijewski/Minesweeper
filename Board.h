#pragma once
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "TextureManager.h"
#include "Random.h"
using namespace std;
class Tile
{
public:
	sf::Sprite tileHidden;
	sf::Sprite tileRevealed;
	sf::Sprite flag;
	sf::Sprite numOne;
	sf::Sprite numTwo;
	sf::Sprite numThree;
	sf::Sprite numFour;
	sf::Sprite numFive;
	sf::Sprite numSix;
	sf::Sprite numSeven;
	sf::Sprite numEight;
	bool isAMine;
	bool isRevealed;
	bool isFlag;
	bool alreadyFlag;
	bool isNumber;
	sf::Vector2f location;
	sf::FloatRect GetSpriteRect();
	vector<Tile*> adjacentTiles;
	Tile();
	Tile* firstAdjacent;
	Tile* secondAdjacent;
	Tile* thirdAdjacent;
	Tile* fourthAdjacent;
	Tile* fifthAdjacent;
	Tile* sixthAdjacent;
	Tile* seventhAdjacent;
	Tile* eighthAdjacent;
};
class Board
{

public:
	vector<Tile> tiles;
	vector <sf::Vector2f> mines;
	sf::Sprite zeroOrNegative;
	sf::Sprite thirdDigit;
	sf::Sprite secondDigit;
	sf::Sprite firstDigit;
	sf::Sprite happyFace;
	int tileCount;
	int windowWidth;
	int windowHeight;
	int mineVsFlagCount;
	bool wasNegative;
	bool gameOver;
	bool gameWon;
	int adjacentMineCount;
	int mineCount;
	bool debugPressed;
	bool alreadyDebugPressed;
	
	


};

