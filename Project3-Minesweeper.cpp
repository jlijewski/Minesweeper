#include <SFML/Graphics.hpp> 
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "TextureManager.h"
#include "Random.h"
#include "Board.h"
using namespace std;

//************************************************MAKE SURE TO CHANGE ALL PATHS BEFORE SUBMITTING-EVEN IN .CPP FILES************************************************//
Board setUpBoard(std::string filePath, Board gameBoard, bool isTestOne, bool isTestTwo, bool isTestThree)
{
    ifstream inFile(filePath);
    string numOfColumnsString;
    getline(inFile, numOfColumnsString);
    int numOfColumns = stoi(numOfColumnsString);

    string numOfRowsString;
    getline(inFile, numOfRowsString);
    int numOfRows = stoi(numOfRowsString);

    string numOfMinesString;
    getline(inFile, numOfMinesString);
    int numOfMines = stoi(numOfMinesString);

    gameBoard.windowWidth = numOfColumns * 32;
    gameBoard.windowHeight = (numOfRows * 32) + 88;

    gameBoard.mineCount = numOfMines;
    gameBoard.tileCount = numOfColumns * numOfRows;





    

    


    for (unsigned int i = 0; i < gameBoard.tileCount; i++) //creating the tiles in the vector of tiles
    {
        gameBoard.tiles.push_back(Tile());
    }
    
    for (unsigned int i = 0, width = 0, height = 0; i < gameBoard.tileCount; i++) //giving each tile a location 
    {

        sf::Vector2f tempLocation(width, height);
        gameBoard.tiles.at(i).location = tempLocation;

        width += 32;
        if (width == gameBoard.windowWidth)
        {
            width = 0;
            height += 32;
        }
    }

    vector<int>uniqueNumbers;
    bool isAlreadyChosen = false;
    int tempMineCount = 10000;
    int i = 0;
    int accessCounter = 0;
    while (i < tempMineCount) //creating the random mine locations and putting them into the mine vector
    {

        int tempRandomNum = Random::Int(0, gameBoard.tiles.size() - 1);

        for (unsigned int i = 0; i < uniqueNumbers.size(); i++)
        {
            if (tempRandomNum == uniqueNumbers.at(i))
            {
                isAlreadyChosen = true;

            }
        }
        uniqueNumbers.push_back(tempRandomNum);
        if (isAlreadyChosen != true)
        {
            accessCounter++;
            int tempWidth = gameBoard.tiles.at(tempRandomNum).location.x;
            int tempHeight = gameBoard.tiles.at(tempRandomNum).location.y;
            gameBoard.tiles.at(tempRandomNum).isAMine = true;
            gameBoard.mines.push_back(sf::Vector2f(tempWidth, tempHeight));
        }
        if (gameBoard.mines.size() == gameBoard.mineCount)
        {
            break;
        }
        isAlreadyChosen = false;
        i++;
    }
    for (unsigned int i = 0; i < gameBoard.tileCount; i++)
    {
        gameBoard.tiles.at(i).isRevealed = false;
        gameBoard.tiles.at(i).isFlag = false;
        gameBoard.tiles.at(i).alreadyFlag = false;
        gameBoard.tiles.at(i).isNumber = false;
    }
    gameBoard.debugPressed = false;
    gameBoard.alreadyDebugPressed = false;
    for (unsigned int i = 0, columnCount = 1, rowCount = 1; i < gameBoard.tileCount; i++)
    {

        if (columnCount == 1 && rowCount == 1)
        {


            gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);


            gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);


            gameBoard.tiles.at(i).eighthAdjacent = &gameBoard.tiles.at((i + 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).eighthAdjacent);


            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;

        }

        if (columnCount == numOfColumns && rowCount == 1)
        {


            gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);

            gameBoard.tiles.at(i).sixthAdjacent = &gameBoard.tiles.at((i - 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).sixthAdjacent);


            gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);



            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }
        if (i == ((gameBoard.tileCount)-numOfColumns))
        {


            gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);




            gameBoard.tiles.at(i).thirdAdjacent = &gameBoard.tiles.at((i + 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).thirdAdjacent);




            gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);




            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }
        if (i == gameBoard.tileCount - 1)
        {


            gameBoard.tiles.at(i).firstAdjacent = &gameBoard.tiles.at((i - 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).firstAdjacent);





            gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);



            gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);




            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }
        if (columnCount == 1)
        {

            gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - (numOfColumns));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);


            gameBoard.tiles.at(i).thirdAdjacent = &gameBoard.tiles.at((i + 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).thirdAdjacent);


            gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);


            gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + (numOfColumns - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);

            gameBoard.tiles.at(i).eighthAdjacent = &gameBoard.tiles.at((i + 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).eighthAdjacent);




            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }
        if (rowCount == 1)
        {


            gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);





            gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);





            gameBoard.tiles.at(i).sixthAdjacent = &gameBoard.tiles.at((i - 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).sixthAdjacent);







            gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);






            gameBoard.tiles.at(i).eighthAdjacent = &gameBoard.tiles.at((i + 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).eighthAdjacent);



            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }

        if (rowCount == numOfRows)
        {


            gameBoard.tiles.at(i).firstAdjacent = &gameBoard.tiles.at((i - 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).firstAdjacent);





            gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);






            gameBoard.tiles.at(i).thirdAdjacent = &gameBoard.tiles.at((i + 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).thirdAdjacent);






            gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);




            gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);




            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;

        }
        if (columnCount == numOfColumns)
        {


            gameBoard.tiles.at(i).firstAdjacent = &gameBoard.tiles.at((i - 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).firstAdjacent);






            gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);




            gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);




            gameBoard.tiles.at(i).sixthAdjacent = &gameBoard.tiles.at((i - 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).sixthAdjacent);






            gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);




            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }




        gameBoard.tiles.at(i).firstAdjacent = &gameBoard.tiles.at((i - 1) - numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).firstAdjacent);



        gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);




        gameBoard.tiles.at(i).thirdAdjacent = &gameBoard.tiles.at((i + 1) - numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).thirdAdjacent);




        gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);





        gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);




        gameBoard.tiles.at(i).sixthAdjacent = &gameBoard.tiles.at((i - 1) + numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).sixthAdjacent);




        gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);



        gameBoard.tiles.at(i).eighthAdjacent = &gameBoard.tiles.at((i + 1) + numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).eighthAdjacent);



        if (columnCount == numOfColumns)
        {
            columnCount = 1;
            rowCount++;
        }
        else
        {
            columnCount++;
        }

    }

    gameBoard.adjacentMineCount = 0;


    

   return gameBoard;
}
Board resetBoard(Board gameBoard, bool isTestOne, bool isTestTwo, bool isTestThree)
{
    gameBoard.mines.clear();
    
    for (unsigned int i = 0; i < gameBoard.tileCount; i++)
    {
        gameBoard.tiles.at(i).isAMine = false;
    }
    if (isTestOne == true)
    {
        
        ifstream file("boards/testboard1.brd");

        if (file.is_open())
        {
            char spot;
            for (int i = 0; i < gameBoard.tileCount; i++)
            {
                file >> spot;
                
                if (spot == '1')
                {
                    gameBoard.tiles.at(i).isAMine = true;
                    int tempWidth = gameBoard.tiles.at(i).location.x;
                    int tempHeight = gameBoard.tiles.at(i).location.y;
                    
                    gameBoard.mines.push_back(sf::Vector2f(tempWidth, tempHeight));
                    
                }
            }
        }
        file.close();
    }
    else if (isTestTwo == true)
    {
        ifstream file("boards/testboard2.brd");

        if (file.is_open())
        {
            char spot;
            for (int i = 0; i < gameBoard.tileCount; i++)
            {
                file >> spot;

                if (spot == '1')
                {
                    gameBoard.tiles.at(i).isAMine = true;
                    int tempWidth = gameBoard.tiles.at(i).location.x;
                    int tempHeight = gameBoard.tiles.at(i).location.y;

                    gameBoard.mines.push_back(sf::Vector2f(tempWidth, tempHeight));

                }
            }
        }
        file.close();
    }
    else if (isTestThree == true)
    {
        ifstream file("boards/testboard3.brd");

        if (file.is_open())
        {
            char spot;
            for (int i = 0; i < gameBoard.tileCount; i++)
            {
                file >> spot;

                if (spot == '1')
                {
                    gameBoard.tiles.at(i).isAMine = true;
                    int tempWidth = gameBoard.tiles.at(i).location.x;
                    int tempHeight = gameBoard.tiles.at(i).location.y;

                    gameBoard.mines.push_back(sf::Vector2f(tempWidth, tempHeight));

                }
            }
        }
        file.close();
    }
    else
    {



        vector<int>uniqueNumbers;
        
        bool isAlreadyChosen = false;
        int tempMineCount = 10000;
        int i = 0;
        int accessCounter = 0;
        
        while (i < tempMineCount) //creating the random mine locations and putting them into the mine vector
        {

            int tempRandomNum = Random::Int(0, gameBoard.tiles.size() - 1);

            for (unsigned int i = 0; i < uniqueNumbers.size(); i++)
            {
                if (tempRandomNum == uniqueNumbers.at(i))
                {
                    isAlreadyChosen = true;

                }
            }
            uniqueNumbers.push_back(tempRandomNum);
            if (isAlreadyChosen != true)
            {
                accessCounter++;
                int tempWidth = gameBoard.tiles.at(tempRandomNum).location.x;
                int tempHeight = gameBoard.tiles.at(tempRandomNum).location.y;
                gameBoard.tiles.at(tempRandomNum).isAMine = true;
                gameBoard.mines.push_back(sf::Vector2f(tempWidth, tempHeight));
                
            }
            if (gameBoard.mines.size() == gameBoard.mineCount)
            {
                break;
            }
            isAlreadyChosen = false;
            i++;
        }
    }
    int numOfColumns = gameBoard.windowWidth / 32;
    int numOfRows = (gameBoard.windowHeight - 88) / 32;
    for (unsigned int i = 0, columnCount = 1, rowCount = 1; i < gameBoard.tileCount; i++)
    {

        if (columnCount == 1 && rowCount == 1)
        {


            gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);


            gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);


            gameBoard.tiles.at(i).eighthAdjacent = &gameBoard.tiles.at((i + 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).eighthAdjacent);


            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;

        }

        if (columnCount == numOfColumns && rowCount == 1)
        {


            gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);

            gameBoard.tiles.at(i).sixthAdjacent = &gameBoard.tiles.at((i - 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).sixthAdjacent);


            gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);



            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }
        if (i == ((gameBoard.tileCount) - numOfColumns))
        {


            gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);




            gameBoard.tiles.at(i).thirdAdjacent = &gameBoard.tiles.at((i + 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).thirdAdjacent);




            gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);




            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }
        if (i == gameBoard.tileCount - 1)
        {


            gameBoard.tiles.at(i).firstAdjacent = &gameBoard.tiles.at((i - 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).firstAdjacent);





            gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);



            gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);




            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }
        if (columnCount == 1)
        {

            gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - (numOfColumns));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);


            gameBoard.tiles.at(i).thirdAdjacent = &gameBoard.tiles.at((i + 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).thirdAdjacent);


            gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);


            gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + (numOfColumns - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);

            gameBoard.tiles.at(i).eighthAdjacent = &gameBoard.tiles.at((i + 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).eighthAdjacent);




            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }
        if (rowCount == 1)
        {


            gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);





            gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);





            gameBoard.tiles.at(i).sixthAdjacent = &gameBoard.tiles.at((i - 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).sixthAdjacent);







            gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);






            gameBoard.tiles.at(i).eighthAdjacent = &gameBoard.tiles.at((i + 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).eighthAdjacent);



            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }

        if (rowCount == numOfRows)
        {


            gameBoard.tiles.at(i).firstAdjacent = &gameBoard.tiles.at((i - 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).firstAdjacent);





            gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);






            gameBoard.tiles.at(i).thirdAdjacent = &gameBoard.tiles.at((i + 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).thirdAdjacent);






            gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);




            gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);




            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;

        }
        if (columnCount == numOfColumns)
        {


            gameBoard.tiles.at(i).firstAdjacent = &gameBoard.tiles.at((i - 1) - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).firstAdjacent);






            gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);




            gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);




            gameBoard.tiles.at(i).sixthAdjacent = &gameBoard.tiles.at((i - 1) + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).sixthAdjacent);






            gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + numOfColumns);
            gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);




            if (columnCount == numOfColumns)
            {
                columnCount = 1;
                rowCount++;
            }
            else
            {
                columnCount++;
            }
            continue;
        }




        gameBoard.tiles.at(i).firstAdjacent = &gameBoard.tiles.at((i - 1) - numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).firstAdjacent);



        gameBoard.tiles.at(i).secondAdjacent = &gameBoard.tiles.at(i - numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).secondAdjacent);




        gameBoard.tiles.at(i).thirdAdjacent = &gameBoard.tiles.at((i + 1) - numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).thirdAdjacent);




        gameBoard.tiles.at(i).fourthAdjacent = &gameBoard.tiles.at((i - 1));
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fourthAdjacent);





        gameBoard.tiles.at(i).fifthAdjacent = &gameBoard.tiles.at(i + 1);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).fifthAdjacent);




        gameBoard.tiles.at(i).sixthAdjacent = &gameBoard.tiles.at((i - 1) + numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).sixthAdjacent);




        gameBoard.tiles.at(i).seventhAdjacent = &gameBoard.tiles.at(i + numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).seventhAdjacent);



        gameBoard.tiles.at(i).eighthAdjacent = &gameBoard.tiles.at((i + 1) + numOfColumns);
        gameBoard.tiles.at(i).adjacentTiles.push_back(gameBoard.tiles.at(i).eighthAdjacent);



        if (columnCount == numOfColumns)
        {
            columnCount = 1;
            rowCount++;
        }
        else
        {
            columnCount++;
        }

    }
    return gameBoard;
}
Tile checkNeighbors(Tile tile)
{
    int adjacentMines = 0;
    for (unsigned int i = 0; i < tile.adjacentTiles.size(); i++)
    {
        if (tile.adjacentTiles.at(i)->isAMine == true)
        {
            adjacentMines++;
        }
    }
    if (adjacentMines == 0)
    {
        for (unsigned int i = 0; i < tile.adjacentTiles.size(); i++)
        {
            if (tile.adjacentTiles.at(i)->isRevealed == false && tile.adjacentTiles.at(i)->isFlag == false)
            {
                tile.adjacentTiles.at(i)->isRevealed = true;
            }
        }
        for (unsigned int i = 0; i < tile.adjacentTiles.size(); i++)
        {
            checkNeighbors(*(tile.adjacentTiles.at(i)));
        }
    }
    adjacentMines = 0;
    return tile;
}
int main()
{
    
    Board gameBoard = setUpBoard("boards/config.cfg", gameBoard, false, false, false);
    bool gameOver = false;
    bool gameWon = false;

    int tempCounterWidth = 0;

    int tempCounterHeight = gameBoard.windowHeight - 88;
    sf::Sprite zeroOrNegative;
    zeroOrNegative.setTexture(TextureManager::GetTexture("digits"));
    zeroOrNegative.setPosition(tempCounterWidth, tempCounterHeight);

    tempCounterWidth += 21;

    sf::Sprite thirdDigit;
    thirdDigit.setTexture(TextureManager::GetTexture("digits"));
    thirdDigit.setPosition(tempCounterWidth, tempCounterHeight);
    tempCounterWidth += 21;

    sf::Sprite secondDigit;
    secondDigit.setTexture(TextureManager::GetTexture("digits"));
    secondDigit.setPosition(tempCounterWidth, tempCounterHeight);

    tempCounterWidth += 21;

    sf::Sprite firstDigit;
    firstDigit.setTexture(TextureManager::GetTexture("digits"));
    firstDigit.setPosition(tempCounterWidth, tempCounterHeight);
    tempCounterWidth += 21;

    gameBoard.mineVsFlagCount = gameBoard.mineCount;
    gameBoard.wasNegative = false;
    gameBoard.gameOver = false;
    gameBoard.gameWon = false;
    
   
  //TEST//
    //int minecounttest = 0;
    //
    //for (unsigned int i = 0; i < gameboard.tiles.size(); i++)
    //{
    //   
    //    if (gameboard.tiles.at(i).isamine == true)
    //    {
    //        
    //        minecounttest++;
    //    }
    //}
    //
    //cout << minecounttest << endl;
      

    sf::RenderWindow window(sf::VideoMode(gameBoard.windowWidth, gameBoard.windowHeight), "Minesweeper");
    
    while (window.isOpen())
    {
        sf::Event event;


        sf::Sprite happyFace(TextureManager::GetTexture("face_happy"));
        int halfWidth = gameBoard.windowWidth / 2;
        happyFace.setPosition(halfWidth - 48, gameBoard.windowHeight - 88);

        sf::Sprite loseFace(TextureManager::GetTexture("face_lose"));
        loseFace.setPosition(happyFace.getPosition());

        sf::Sprite winFace(TextureManager::GetTexture("face_win"));
        winFace.setPosition(happyFace.getPosition());

        sf::Sprite debugImage(TextureManager::GetTexture("debug"));
        debugImage.setPosition((halfWidth - 48) + 128, gameBoard.windowHeight - 88);

        sf::Sprite test1Image(TextureManager::GetTexture("test_1"));
        test1Image.setPosition((halfWidth - 48) + 192, gameBoard.windowHeight - 88);

        sf::Sprite test2Image(TextureManager::GetTexture("test_2"));
        test2Image.setPosition((halfWidth - 48) + 256, gameBoard.windowHeight - 88);

        sf::Sprite test3Image(TextureManager::GetTexture("test_3"));
        test3Image.setPosition((halfWidth - 48) + 320, gameBoard.windowHeight - 88);


        while (window.pollEvent(event))
        {
           

            if (event.type == sf::Event::Closed)
                window.close();
            
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (gameOver == true)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i position = sf::Mouse::getPosition(window);
                        if (loseFace.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {
                            
                                gameOver = false;
                                for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                                {
                                    gameBoard.tiles.at(i).isRevealed = false;
                                    gameBoard.tiles.at(i).isFlag = false;
                                    gameBoard.tiles.at(i).alreadyFlag = false;
                                    gameBoard.tiles.at(i).isNumber = false;
                                    gameBoard.tiles.at(i).adjacentTiles.clear();
                                }

                                gameBoard = resetBoard(gameBoard, false, false, false);
                                gameBoard.mineCount = gameBoard.mines.size();
                                gameBoard.mineVsFlagCount = gameBoard.mineCount;
                            
                        }
                        if (test1Image.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {
                            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                            {
                                gameBoard.tiles.at(i).isRevealed = false;
                                gameBoard.tiles.at(i).isFlag = false;
                                gameBoard.tiles.at(i).alreadyFlag = false;
                                gameBoard.tiles.at(i).isNumber = false;
                                gameBoard.tiles.at(i).adjacentTiles.clear();
                            }

                            gameBoard = resetBoard(gameBoard, true, false, false);

                            gameBoard.mineVsFlagCount = gameBoard.mines.size();
                            gameOver = false;
                        }
                        if (test2Image.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {
                            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                            {
                                gameBoard.tiles.at(i).isRevealed = false;
                                gameBoard.tiles.at(i).isFlag = false;
                                gameBoard.tiles.at(i).alreadyFlag = false;
                                gameBoard.tiles.at(i).isNumber = false;
                                gameBoard.tiles.at(i).adjacentTiles.clear();
                            }

                            gameBoard = resetBoard(gameBoard, false, true, false);

                            gameBoard.mineVsFlagCount = gameBoard.mines.size();
                            gameOver = false;
                        }
                        if (test3Image.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {
                            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                            {
                                gameBoard.tiles.at(i).isRevealed = false;
                                gameBoard.tiles.at(i).isFlag = false;
                                gameBoard.tiles.at(i).alreadyFlag = false;
                                gameBoard.tiles.at(i).isNumber = false;
                                gameBoard.tiles.at(i).adjacentTiles.clear();
                            }

                            gameBoard = resetBoard(gameBoard, false, false, true);

                            gameBoard.mineVsFlagCount = gameBoard.mines.size();
                            gameOver = false;
                        }
                    }

                }
                else if (gameWon == true)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i position = sf::Mouse::getPosition(window);
                        if (winFace.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {

                            gameWon = false;
                            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                            {
                                gameBoard.tiles.at(i).isRevealed = false;
                                gameBoard.tiles.at(i).isFlag = false;
                                gameBoard.tiles.at(i).alreadyFlag = false;
                                gameBoard.tiles.at(i).isNumber = false;
                                gameBoard.tiles.at(i).adjacentTiles.clear();
                            }

                            gameBoard = resetBoard(gameBoard, false, false, false);
                            gameBoard.mineCount = gameBoard.mines.size();
                            gameBoard.mineVsFlagCount = gameBoard.mineCount;

                        }
                        if (test1Image.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {
                            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                            {
                                gameBoard.tiles.at(i).isRevealed = false;
                                gameBoard.tiles.at(i).isFlag = false;
                                gameBoard.tiles.at(i).alreadyFlag = false;
                                gameBoard.tiles.at(i).isNumber = false;
                                gameBoard.tiles.at(i).adjacentTiles.clear();
                            }

                            gameBoard = resetBoard(gameBoard, true, false, false);

                            gameBoard.mineVsFlagCount = gameBoard.mines.size();
                            gameWon = false;
                        }
                        if (test2Image.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {
                            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                            {
                                gameBoard.tiles.at(i).isRevealed = false;
                                gameBoard.tiles.at(i).isFlag = false;
                                gameBoard.tiles.at(i).alreadyFlag = false;
                                gameBoard.tiles.at(i).isNumber = false;
                                gameBoard.tiles.at(i).adjacentTiles.clear();
                            }

                            gameBoard = resetBoard(gameBoard, false, true, false);

                            gameBoard.mineVsFlagCount = gameBoard.mines.size();
                            gameWon = false;
                        }
                        if (test3Image.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {
                            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                            {
                                gameBoard.tiles.at(i).isRevealed = false;
                                gameBoard.tiles.at(i).isFlag = false;
                                gameBoard.tiles.at(i).alreadyFlag = false;
                                gameBoard.tiles.at(i).isNumber = false;
                                gameBoard.tiles.at(i).adjacentTiles.clear();
                            }

                            gameBoard = resetBoard(gameBoard, false, false, true);

                            gameBoard.mineVsFlagCount = gameBoard.mines.size();
                            gameWon = false;
                        }
                    }
                }
                else
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i position = sf::Mouse::getPosition(window);
                        for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                        {

                            if (gameBoard.tiles.at(i).GetSpriteRect().contains(sf::Vector2f(position.x, position.y)))
                            {
                                if (gameBoard.tiles.at(i).isFlag == true)
                                {
                                    gameBoard.tiles.at(i).isRevealed = false;
                                }
                                else
                                {
                                    gameBoard.tiles.at(i).isRevealed = true;
                                }
                            }
                           

                        }
                        if (happyFace.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {


                            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                            {
                                gameBoard.tiles.at(i).isRevealed = false;
                                gameBoard.tiles.at(i).isFlag = false;
                                gameBoard.tiles.at(i).alreadyFlag = false;
                                gameBoard.tiles.at(i).isNumber = false;
                                gameBoard.tiles.at(i).adjacentTiles.clear();
                            }

                            gameBoard = resetBoard(gameBoard, false, false, false);
                            gameBoard.mineCount = gameBoard.mines.size();
                            gameBoard.mineVsFlagCount = gameBoard.mineCount;
                            


                        }
                        if (debugImage.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {
                            if (gameBoard.alreadyDebugPressed == true)
                            {
                                gameBoard.alreadyDebugPressed = false;
                                gameBoard.debugPressed = false;
                            }
                            else
                            {
                                gameBoard.alreadyDebugPressed = true;
                                gameBoard.debugPressed = true;
                            }
                        }
                        if (test1Image.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {
                            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                            {
                                gameBoard.tiles.at(i).isRevealed = false;
                                gameBoard.tiles.at(i).isFlag = false;
                                gameBoard.tiles.at(i).alreadyFlag = false;
                                gameBoard.tiles.at(i).isNumber = false;
                                gameBoard.tiles.at(i).adjacentTiles.clear();
                            }

                            gameBoard = resetBoard(gameBoard, true, false, false);
              
                            gameBoard.mineVsFlagCount = gameBoard.mines.size();
                        }
                        if (test2Image.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {
                            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                            {
                                gameBoard.tiles.at(i).isRevealed = false;
                                gameBoard.tiles.at(i).isFlag = false;
                                gameBoard.tiles.at(i).alreadyFlag = false;
                                gameBoard.tiles.at(i).isNumber = false;
                                gameBoard.tiles.at(i).adjacentTiles.clear();
                            }

                            gameBoard = resetBoard(gameBoard, false, true, false);
                            
                            gameBoard.mineVsFlagCount = gameBoard.mines.size();
                        }
                        if (test3Image.getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
                        {
                            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                            {
                                gameBoard.tiles.at(i).isRevealed = false;
                                gameBoard.tiles.at(i).isFlag = false;
                                gameBoard.tiles.at(i).alreadyFlag = false;
                                gameBoard.tiles.at(i).isNumber = false;
                                gameBoard.tiles.at(i).adjacentTiles.clear();
                            }

                            gameBoard = resetBoard(gameBoard, false, false, true);

                            gameBoard.mineVsFlagCount = gameBoard.mines.size();
                        }
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        sf::Vector2i positionRight = sf::Mouse::getPosition(window);
                        for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                        {

                            if (gameBoard.tiles.at(i).GetSpriteRect().contains(sf::Vector2f(positionRight.x, positionRight.y)))
                            {
                                if (gameBoard.tiles.at(i).alreadyFlag == true)
                                {
                                    gameBoard.tiles.at(i).isFlag = false;
                                    gameBoard.tiles.at(i).alreadyFlag = false;
                                    if (gameBoard.tiles.at(i).isRevealed == false)
                                    {
                                        gameBoard.mineVsFlagCount++;
                                    }

                                }
                                else
                                {
                                    gameBoard.tiles.at(i).isFlag = true;
                                    gameBoard.tiles.at(i).alreadyFlag = true;

                                    if (gameBoard.tiles.at(i).isRevealed == false)
                                    {
                                        gameBoard.mineVsFlagCount--;
                                    }


                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear();

        if (gameOver == true)
        {
            window.draw(loseFace);
        }
        else if (gameWon == true)
        {
            window.draw(winFace);
        }
        else
        {
            window.draw(happyFace);
        }
        
       


        
        window.draw(debugImage);

        
        window.draw(test1Image);

        
        window.draw(test2Image);

        
        window.draw(test3Image);
       
       
        
        
            //Prints out revealed tiles//

            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
            {



                if (gameBoard.tiles.at(i).isFlag == false)
                {
                    int tempWidth = gameBoard.tiles.at(i).location.x;
                    int tempHeight = gameBoard.tiles.at(i).location.y;

                    gameBoard.tiles.at(i).tileHidden.setPosition(tempWidth, tempHeight);
                    window.draw(gameBoard.tiles.at(i).tileHidden);
                }
                if (gameBoard.tiles.at(i).isRevealed == false)//draws out the hidden tile if tile has not been clicked
                {
                    int tempWidth = gameBoard.tiles.at(i).location.x;
                    int tempHeight = gameBoard.tiles.at(i).location.y;

                    gameBoard.tiles.at(i).tileHidden.setPosition(tempWidth, tempHeight);
                    window.draw(gameBoard.tiles.at(i).tileHidden);
                    if (gameBoard.tiles.at(i).isFlag == true)//draws flag if a tile is right-clicked
                    {
                        gameBoard.tiles.at(i).flag.setPosition(tempWidth, tempHeight);
                        window.draw(gameBoard.tiles.at(i).flag);
                    }
                }

                else if (gameBoard.tiles.at(i).isRevealed == true)//draws out the revelead tile if the tile has been clicked
                {
                    int tempWidth = gameBoard.tiles.at(i).location.x;
                    int tempHeight = gameBoard.tiles.at(i).location.y;


                    gameBoard.tiles.at(i).tileRevealed.setPosition(tempWidth, tempHeight);
                    window.draw(gameBoard.tiles.at(i).tileRevealed);
                    if (gameBoard.tiles.at(i).isAMine == true)//draws the mine if the tile has a mine
                    {
                        sf::Sprite mine;
                        mine.setTexture(TextureManager::GetTexture("mine"));
                        mine.setPosition(tempWidth, tempHeight);
                        window.draw(mine);
                        gameOver = true;
                    }
                    else
                    {
                        if (gameBoard.tiles.at(i).isNumber == false)
                        {
                            for (unsigned int j = 0; j < gameBoard.tiles.at(i).adjacentTiles.size(); j++)
                            {
                                if ((gameBoard.tiles.at(i).adjacentTiles.at(j)->isAMine) == true)
                                {
                                    gameBoard.adjacentMineCount++;
                                }
                            }
                            int tempWidth = gameBoard.tiles.at(i).location.x;
                            int tempHeight = gameBoard.tiles.at(i).location.y;
                            if (gameBoard.adjacentMineCount == 0)
                            {
                                for (unsigned int k = 0; k < gameBoard.tiles.at(i).adjacentTiles.size(); k++)
                                {
                                    if (gameBoard.tiles.at(i).adjacentTiles.at(k)->isFlag == false)
                                    {
                                        gameBoard.tiles.at(i).adjacentTiles.at(k)->isRevealed = true;
                                    }
                                }
                            }
                            if (gameBoard.adjacentMineCount == 1)
                            {
                                gameBoard.tiles.at(i).numOne.setPosition(tempWidth, tempHeight);
                                window.draw(gameBoard.tiles.at(i).numOne);
                                gameBoard.adjacentMineCount = 0;
                                gameBoard.tiles.at(i).isNumber == true;
                            }
                            if (gameBoard.adjacentMineCount == 2)
                            {

                                gameBoard.tiles.at(i).numTwo.setPosition(tempWidth, tempHeight);
                                window.draw(gameBoard.tiles.at(i).numTwo);
                                gameBoard.adjacentMineCount = 0;
                                gameBoard.tiles.at(i).isNumber == true;
                            }
                            if (gameBoard.adjacentMineCount == 3)
                            {
                                gameBoard.tiles.at(i).numThree.setPosition(tempWidth, tempHeight);
                                window.draw(gameBoard.tiles.at(i).numThree);
                                gameBoard.adjacentMineCount = 0;
                                gameBoard.tiles.at(i).isNumber == true;
                            }
                            if (gameBoard.adjacentMineCount == 4)
                            {
                                gameBoard.tiles.at(i).numFour.setPosition(tempWidth, tempHeight);
                                window.draw(gameBoard.tiles.at(i).numFour);
                                gameBoard.adjacentMineCount = 0;
                                gameBoard.tiles.at(i).isNumber == true;
                            }
                            if (gameBoard.adjacentMineCount == 5)
                            {
                                gameBoard.tiles.at(i).numFive.setPosition(tempWidth, tempHeight);
                                window.draw(gameBoard.tiles.at(i).numFive);
                                gameBoard.adjacentMineCount = 0;
                                gameBoard.tiles.at(i).isNumber == true;
                            }
                            if (gameBoard.adjacentMineCount == 6)
                            {
                                gameBoard.tiles.at(i).numSix.setPosition(tempWidth, tempHeight);
                                window.draw(gameBoard.tiles.at(i).numSix);
                                gameBoard.adjacentMineCount = 0;
                                gameBoard.tiles.at(i).isNumber == true;
                            }
                            if (gameBoard.adjacentMineCount == 7)
                            {
                                gameBoard.tiles.at(i).numSeven.setPosition(tempWidth, tempHeight);
                                window.draw(gameBoard.tiles.at(i).numSeven);
                                gameBoard.adjacentMineCount = 0;
                                gameBoard.tiles.at(i).isNumber == true;
                            }
                            if (gameBoard.adjacentMineCount == 8)
                            {
                                gameBoard.tiles.at(i).numEight.setPosition(tempWidth, tempHeight);
                                window.draw(gameBoard.tiles.at(i).numEight);
                                gameBoard.adjacentMineCount = 0;
                                gameBoard.tiles.at(i).isNumber == true;
                            }
                            gameBoard.adjacentMineCount = 0;
                        }


                    }

                }


            }
            int tileRevealedCount = 0;
            for (unsigned int i = 0; i < gameBoard.tileCount; i++)
            {
                if (gameBoard.tiles.at(i).isRevealed)
                {
                    tileRevealedCount++;
                }
            }
            if (tileRevealedCount == gameBoard.tileCount - gameBoard.mines.size())
            {
                gameWon = true;
                tileRevealedCount = 0;
            }
            else
            {
                tileRevealedCount = 0;
            }
            if (gameBoard.debugPressed == true)
            {
                for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                {
                    if (gameBoard.tiles.at(i).isAMine == true)
                    {
                        int tempWidthDebug = gameBoard.tiles.at(i).location.x;
                        int tempHeightDebug = gameBoard.tiles.at(i).location.y;
                        sf::Sprite mine;
                        mine.setTexture(TextureManager::GetTexture("mine"));
                        mine.setPosition(tempWidthDebug, tempHeightDebug);
                        window.draw(mine);
                    }
                }
            }
            if (gameOver == true)
            {
                for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                {


                    if (gameBoard.tiles.at(i).isAMine == true)
                    {
                        if (gameBoard.tiles.at(i).isFlag)
                        {
                            int tempWidthFlag = gameBoard.tiles.at(i).location.x;
                            int tempHeightFlag = gameBoard.tiles.at(i).location.y;
                            sf::Sprite mine;
                            mine.setTexture(TextureManager::GetTexture("mine"));
                            mine.setPosition(tempWidthFlag, tempHeightFlag);
                            window.draw(mine);
                        }
                        else
                        {
                            gameBoard.tiles.at(i).isRevealed = true;
                        }


                    }

                }
            }
            if (gameWon == true)
            {
                for (unsigned int i = 0; i < gameBoard.tileCount; i++)
                {
                    if (gameBoard.tiles.at(i).isAMine == true)
                    {
                        gameBoard.tiles.at(i).isFlag = true;
                    }
                }
                gameBoard.mineVsFlagCount = 0;
                gameBoard.debugPressed = false;
            }

        
       
        //prints out debug/test buttons//
        

        //Drawing the counter//
        
        
        
        if (gameBoard.mineVsFlagCount < 0)
        {
            
            zeroOrNegative.setTextureRect(sf::IntRect(0 + (21 * 10), 0, 21, 32));
            window.draw(zeroOrNegative);
            gameBoard.mineVsFlagCount = gameBoard.mineVsFlagCount * (-1);
            gameBoard.wasNegative = true;
        }
        
        if (gameBoard.mineVsFlagCount < 100)
        {
            
            int tempThirdDigit = 0;
            thirdDigit.setTextureRect(sf::IntRect(0, 0, 21, 32));
            window.draw(thirdDigit);

            int tempFirstDigit = gameBoard.mineVsFlagCount % 10;
            firstDigit.setTextureRect(sf::IntRect(0 + (21 * tempFirstDigit), 0, 21, 32));
            window.draw(firstDigit);

            int tempSecondDigit = (gameBoard.mineVsFlagCount / 10) % 10;
            secondDigit.setTextureRect(sf::IntRect(0 + (21 * tempSecondDigit), 0, 21, 32));
            window.draw(secondDigit);
        }
        if (gameBoard.mineVsFlagCount >= 100)
        {
            int tempThirdDigit = ((gameBoard.mineVsFlagCount / 10) / 10) % 10;
            thirdDigit.setTextureRect(sf::IntRect(0 + (21 * tempThirdDigit), 0, 21, 32));
            window.draw(thirdDigit);

            int tempFirstDigit = gameBoard.mineVsFlagCount % 10;
            firstDigit.setTextureRect(sf::IntRect(0 + (21 * tempFirstDigit), 0, 21, 32));
            window.draw(firstDigit);

            int tempSecondDigit = (gameBoard.mineVsFlagCount / 10) % 10;
            secondDigit.setTextureRect(sf::IntRect(0 + (21 * tempSecondDigit), 0, 21, 32));
            window.draw(secondDigit);
        }
        if (gameBoard.wasNegative == true)
        {
            gameBoard.mineVsFlagCount = gameBoard.mineVsFlagCount * (-1);
            gameBoard.wasNegative = false;
        }
        
        






        //*******************************************************//
        
       
    
        window.display();
    }
    
    TextureManager::Clear();

    for (unsigned int i = 0; i < gameBoard.tiles.size(); i++)
    {
        for (unsigned int j = 0; j < gameBoard.tiles.at(i).adjacentTiles.size(); j++)
        {
            delete gameBoard.tiles.at(i).adjacentTiles.at(j);
        }
    }
    return 0;
}
