#include "Board.h"
#include "TextureManager.h"


Tile::Tile()
{
	tileHidden.setTexture(TextureManager::GetTexture("tile_hidden"));
	tileRevealed.setTexture(TextureManager::GetTexture("tile_revealed"));
	flag.setTexture(TextureManager::GetTexture("flag"));
	numOne.setTexture(TextureManager::GetTexture("number_1"));
	numTwo.setTexture(TextureManager::GetTexture("number_2"));
	numThree.setTexture(TextureManager::GetTexture("number_3"));
	numFour.setTexture(TextureManager::GetTexture("number_4"));
	numFive.setTexture(TextureManager::GetTexture("number_5"));
	numSix.setTexture(TextureManager::GetTexture("number_6"));
	numSeven.setTexture(TextureManager::GetTexture("number_7"));
	numEight.setTexture(TextureManager::GetTexture("number_8"));

	bool isAMine = false;
	bool isRevealed = false;
	bool isFlag = false;
	bool alreadyFlag = false;
}
sf::FloatRect Tile::GetSpriteRect()
{
	
	return tileHidden.getGlobalBounds();
	
}




