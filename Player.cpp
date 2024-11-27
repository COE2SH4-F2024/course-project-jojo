#include "Player.h"
#include "iostream"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP; 

    // more actions to be included
    playerPos.pos -> x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.pos -> y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '@';
}


Player::~Player()
{
    // delete any heap members here
    //no keyword "new" in the constructor, hence no heap memever
    
    //this can be empty
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{

    char input = mainGameMechsRef->getInput();

    // PPA3 input processing logic
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case ' ':  // exit
                mainGameMechsRef->setExitTrue(); 
                break;
            case 119: //w
                if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                {
                    myDir = UP;
                }
                break;
            case 115: //s
                if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                {
                    myDir = DOWN;
                }
                break;

            case 97: //a
                if (myDir == DOWN || myDir == UP || myDir == STOP)
                {
                    myDir = LEFT;
                }               
                break;

            case 100: //d
                if (myDir == DOWN || myDir == UP || myDir == STOP)
                {
                    myDir = RIGHT;
                } 
                break;  
            default:
                break;
        }
        mainGameMechsRef->setInput(0);
    }

}

void Player::movePlayer()
{

    if (myDir == UP)
    {
        if (playerPos.pos -> y == 1)
        {
            playerPos.pos -> y = mainGameMechsRef->getBoardSizeY() - 2;
        }
        else {
            playerPos.pos -> y = playerPos.pos -> y - 1;
        }
    }

    if (myDir == DOWN)
    {
        if (playerPos.pos -> y == mainGameMechsRef->getBoardSizeY() - 2)
        {
            playerPos.pos -> y = 1;
        }
        else {
            playerPos.pos -> y = playerPos.pos -> y + 1;
        }
    }

    if (myDir == LEFT)
    {
        if (playerPos.pos -> x == 1)
        {
            playerPos.pos -> x = mainGameMechsRef->getBoardSizeX() - 2;
        }
        else {
            playerPos.pos -> x = playerPos.pos -> x - 1;
        }
    }

    if (myDir == RIGHT)
    {
        if (playerPos.pos -> x == mainGameMechsRef->getBoardSizeX() - 2)
        {
            playerPos.pos -> x = 1;
        }
        else {
            playerPos.pos -> x = playerPos.pos -> x + 1;
        }
    }
}

// More methods to be added