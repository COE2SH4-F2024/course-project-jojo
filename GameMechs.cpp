#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
        input = 0 ;
        exitFlag = false;
        loseFlag = false;
        score = 0;

        boardSizeX = 20;
        boardSizeY = 10; 
}

GameMechs::GameMechs(int boardX, int boardY)
{
        input = 0;
        exitFlag = false;
        loseFlag = false;
        score = 0;

        boardSizeX = boardX;
        boardSizeY = boardX; 
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    //no "new" so no destructor
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    if (MacUILib_hasChar())
    {
        char input = MacUILib_getChar();
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
    loseFlag = false;
}

void GameMechs::setInput(char this_input)
{
    if (MacUILib_hasChar())
    {
        input = this_input;
    }
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here