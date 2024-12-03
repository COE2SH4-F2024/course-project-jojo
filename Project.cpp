#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000 // Delay constant for game loop

Player *myPlayer;          // Pointer to Player object
GameMechs *myGM;           // Pointer to GameMechs object
char **gameboard;          // 2D game board representation

int ROW;                   // Number of rows in the game board
int COL;                   // Number of columns in the game board

void Initialize(void);     // Initialization function
void GetInput(void);       // Get user input
void RunLogic(void);       // Update game logic
void DrawScreen(void);     // Render the game board
void LoopDelay(void);      // Introduce delay in the game loop
void CleanUp(void);        // Clean up allocated resources

int main(void)
{
    Initialize();

    while (myGM->getExitFlagStatus() == false) // Main game loop
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myPlayer = new Player(myGM); // Link player and game mechanics

    objPosArrayList* playerPos = myPlayer->getPlayerPos();
    myGM->generateFood(playerPos); // Place food on the board

    ROW = myGM->getBoardSizeY();
    COL = myGM->getBoardSizeX();

    // Allocate memory for game board
    gameboard = new char*[ROW];
    for (int i = 0; i < ROW; i++)
    {
        gameboard[i] = new char[COL];
    }
}

void GetInput(void)
{
    myGM->getInput(); // Fetch input from user
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();   
    myPlayer->movePlayer(); // Move player based on direction

    // Regenerate food if consumed by player
    objPosArrayList* playerPosList = myPlayer->getPlayerPos();
    objPos food = myGM->getFoodPos();
    for (int k = 0; k < playerPosList->getSize(); k++)
    {
        if (playerPosList->getElement(k).pos->x == food.pos->x &&
            playerPosList->getElement(k).pos->y == food.pos->y)
        {
            myGM->generateFood(playerPosList);
        }
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPosArrayList* playerPos = myPlayer->getPlayerPos();
    objPos food = myGM->getFoodPos();
    int playerSize = playerPos->getSize();

    // Draw borders and empty spaces
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            gameboard[i][j] = (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1) ? '#' : ' ';
        }
    }

    // Draw the player
    for (int k = 0; k < playerSize; k++)
    {
        objPos segment = playerPos->getElement(k).getObjPos();
        gameboard[segment.pos->y][segment.pos->x] = segment.getSymbol();
    }

    // Draw the food
    gameboard[food.pos->y][food.pos->x] = food.symbol;

    // Print the game board
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            MacUILib_printf("%c", gameboard[i][j]);
        }
        MacUILib_printf("\n");
    }

    // Display game info
    MacUILib_printf("Player[x,y] = [%d,%d] , %c\nScore: %d", 
        playerPos->getHeadElement().pos->x, 
        playerPos->getHeadElement().pos->y, 
        playerPos->getHeadElement().symbol, 
        myGM->getScore());

    MacUILib_printf("\n(%d,%d)\n", food.pos->x, food.pos->y);

    // Display exit/lose messages
    if (myGM->getExitFlagStatus() && !myGM->getLoseFlagStatus())
    {
        MacUILib_printf("You exited the game! Sad to see you go!");
    }
    if (myGM->getLoseFlagStatus())
    {
        MacUILib_printf("CANNIBAL ALERT!\nCANNIBAL ALERT!\nYOU JUST LOST! BETTER LUCK NEXT TIME!");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // Introduce delay to control game speed
}

void CleanUp(void)
{
    delete myPlayer;
    delete myGM;

    // Free allocated memory for game board
    for (int i = 0; i < ROW; i++)
    {
        delete[] gameboard[i];
    }
    delete[] gameboard;

    MacUILib_uninit(); // Clean up UI library
}
