#include "Player.h"
#include "iostream"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList(); // Initialize the list to store player positions
    myDir = STOP; // Initial direction is stationary

    // Initialize the snake's head at the center of the board
    playerPosList->insertHead(objPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2,'@'));
}

Player::~Player()
{
    // Clean up heap memory
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList; // Return player's position list
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput(); // Get user input

    if (input != 0) // Process input if it's not null
    {
        switch(input)
        {
            case ' ':  // Exit game
                mainGameMechsRef->setExitTrue();
                break;
            case 119: // 'w': Move up if direction is valid
                if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                    myDir = UP;
                break;
            case 115: // 's': Move down
                if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                    myDir = DOWN;
                break;
            case 97:  // 'a': Move left
                if (myDir == DOWN || myDir == UP || myDir == STOP)
                    myDir = LEFT;
                break;
            case 100: // 'd': Move right
                if (myDir == DOWN || myDir == UP || myDir == STOP)
                    myDir = RIGHT;
                break;
            default: // Ignore invalid input
                break;
        }
        mainGameMechsRef->setInput(0); // Reset input
    }
}

void Player::movePlayer()
{
    objPos temp = playerPosList->getHeadElement().getObjPos(); // Temporary position for head movement
    objPos head = playerPosList->getHeadElement().getObjPos(); // Current head position

    // Update position based on the direction
    if (myDir == UP)
    {
        temp.pos->y = (head.pos->y == 1) ? mainGameMechsRef->getBoardSizeY() - 2 : temp.pos->y - 1;
        playerPosList->insertHead(temp);
        playerPosList->removeTail();
    }
    if (myDir == DOWN)
    {
        temp.pos->y = (head.pos->y == mainGameMechsRef->getBoardSizeY() - 2) ? 1 : temp.pos->y + 1;
        playerPosList->insertHead(temp);
        playerPosList->removeTail();
    }
    if (myDir == LEFT)
    {
        temp.pos->x = (head.pos->x == 1) ? mainGameMechsRef->getBoardSizeX() - 2 : temp.pos->x - 1;
        playerPosList->insertHead(temp);
        playerPosList->removeTail();
    }
    if (myDir == RIGHT)
    {
        temp.pos->x = (head.pos->x == mainGameMechsRef->getBoardSizeX() - 2) ? 1 : temp.pos->x + 1;
        playerPosList->insertHead(temp);
        playerPosList->removeTail();
    }

    // Check for collision with the player's body
    for (int i = 1; i < playerPosList->getSize(); ++i)
    {
        if (playerPosList->getElement(i).getObjPos().isPosEqual(&temp))
        {
            mainGameMechsRef->setLoseFlag();
            return;
        }
    }

    // Check if player eats the food
    if (temp.pos->x == mainGameMechsRef->getFoodPos().pos->x && temp.pos->y == mainGameMechsRef->getFoodPos().pos->y)
    {
        playerPosList->insertHead(temp); // Grow snake
        mainGameMechsRef->incrementScore();
    }
}
