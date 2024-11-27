#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"
#include "GameMechs.h"
using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;

char **gameboard;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int ROW;
int COL;

int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
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

    ROW = myGM->getBoardSizeY();
    COL = myGM->getBoardSizeX();
    
    gameboard = new char*[ROW];
    for (int i = 0 ; i < ROW ; i++)
    {
        gameboard[i] = new char[COL];
    }

    myPlayer = new Player(myGM); //linking so they interact
}

void GetInput(void)
{
    myGM->getInput();
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    //you will need to implement your copy asssignment operator
    // to make line work

    for(int i = 0 ; i < ROW ; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            if( i == 0 || i == ROW-1 || j == 0 || j == COL-1)
                gameboard[i][j] = '#';
            else
                gameboard[i][j] = ' ';
        }
    }

    objPos playerPos = myPlayer->getPlayerPos();

    gameboard[playerPos.pos->y][playerPos.pos->x] = playerPos.symbol;

    for(int i = 0 ; i < ROW ; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            MacUILib_printf("%c" , gameboard[i][j]);
        }
        MacUILib_printf("\n");
    } 
    MacUILib_printf("Player[x,y] = [%d,%d] , %c\n" , playerPos.pos->x, playerPos.pos->y , playerPos.symbol);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  
    delete myPlayer;  
    delete myGM;

    for (int i = 0; i < ROW; i++)
    {
        delete[] gameboard[i];
    }
    delete[] gameboard;
    MacUILib_uninit();
}