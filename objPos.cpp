#include "objPos.h"

// Default constructor
objPos::objPos()
{
    pos = new Pos;  // Dynamically allocate memory for 'pos'
    pos->x = 0;     // Initialize x position to 0
    pos->y = 0;     // Initialize y position to 0
    symbol = 0;     // Initialize symbol to NULL (no symbol)
}

// Parameterized constructor
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;  // Dynamically allocate memory for 'pos'
    pos->x = xPos;  // Set x position to passed value
    pos->y = yPos;  // Set y position to passed value
    symbol = sym;   // Set symbol to passed value
}

// Destructor to clean up dynamically allocated memory
objPos::~objPos()
{
    delete[] pos;  // Deallocate memory for 'pos'
}

// Copy constructor
objPos::objPos(const objPos &d) 
{
    pos = new Pos;         // Allocate new memory for pos
    pos->x = d.pos->x;     // Copy x position from the other object
    pos->y = d.pos->y;     // Copy y position from the other object
    symbol = d.symbol;     // Copy symbol from the other object
}

// Copy assignment operator
objPos& objPos::operator=(const objPos &d)
{
    if (this != &d)  // Check for self-assignment
    {
        pos->x = d.pos->x;  // Copy x position
        pos->y = d.pos->y;  // Copy y position
        symbol = d.symbol;  // Copy symbol
    }
    return *this;  // Return the current object
}

// Set position using another objPos object
void objPos::setObjPos(objPos d)
{
    pos->x = d.pos->x;  // Set x position from passed objPos
    pos->y = d.pos->y;  // Set y position from passed objPos
    symbol = d.symbol;  // Set symbol from passed objPos
}

// Set position using x, y coordinates and a symbol
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;  // Set x position to passed value
    pos->y = yPos;  // Set y position to passed value
    symbol = sym;   // Set symbol to passed value
}

// Get a copy of the current object
objPos objPos::getObjPos() const
{
    objPos returnPos;

    returnPos.pos->x = pos->x;  // Copy x position
    returnPos.pos->y = pos->y;  // Copy y position
    returnPos.symbol = symbol;  // Copy symbol
    
    return returnPos;  // Return the new objPos object
}

// Get the symbol of the current object
char objPos::getSymbol() const
{
    return symbol;  // Return the symbol of the current object
}

// Check if positions of two objPos objects are equal
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);  // Compare x and y positions
}

// Return symbol if positions of two objPos objects are equal, otherwise return 0
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if (isPosEqual(refPos))  // Check if positions are equal
        return symbol;  // Return symbol if positions match
    else
        return 0;  // Return 0 if positions do not match
}
