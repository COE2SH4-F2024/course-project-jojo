#include "GameMechs.h"
#include "MacUILib.h"
#include <cstdlib>
#include <ctime>

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY; // Fix: It should be boardY, not boardX
}

// Destructor: No need for memory cleanup since we aren't dynamically allocating memory in this class
GameMechs::~GameMechs() 
{
    // No "new" memory allocation so no explicit destructor required
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar())  // Check if a character input is available
    {
        input = MacUILib_getChar();  // Read the input
    }

    if (getLoseFlagStatus())  // Check if the game is lost
    {
        setExitTrue();  // Exit the game if the player loses
    }

    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    if (MacUILib_hasChar())  // If the input is available, update it
    {
        input = this_input;
    }
}

void GameMechs::clearInput()
{
    input = 0;  // Clear the input by resetting it to 0 (null character)
}

void GameMechs::generateFood(objPosArrayList* blockOff)
{
    srand(static_cast<unsigned int>(time(NULL)));  // Initialize random seed based on current time

    int randX, randY;
    bool done = false;

    do {
        randX = rand() % (boardSizeX - 2) + 1;  // Generate random x within the board range, excluding borders
        randY = rand() % (boardSizeY - 2) + 1;  // Generate random y within the board range, excluding borders
        
        done = true;  // Assume the position is valid initially

        // Check if the generated food position collides with the player's position
        for (int i = 0; i < blockOff->getSize(); i++)
        {
            if ((randX == blockOff->getElement(i).getObjPos().pos->x && 
                 randY == blockOff->getElement(i).getObjPos().pos->y))
            {
                done = false;  // If there's a collision, generate a new position
                break;
            }
        }

    } while (!done);  // Repeat until a valid position is found

    // Set the food's position and symbol
    foodPos.symbol = 'o';
    foodPos.pos->x = randX;
    foodPos.pos->y = randY;
}

objPos GameMechs::getFoodPos()
{
    return foodPos;  // Return the current food position
}
