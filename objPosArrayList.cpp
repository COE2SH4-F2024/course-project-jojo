#include "objPosArrayList.h"

// Constructor: Initializes the object position array list.
objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // Allocate memory for the list
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;

    // Initialize all elements with default values
    for (int i = 0; i < ARRAY_MAX_CAP; i++) {
        aList[i] = objPos();
    }
}

// Destructor: Frees allocated memory.
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

// Copy Constructor: Creates a deep copy of another objPosArrayList.
objPosArrayList::objPosArrayList(const objPosArrayList &d)
{
    aList = new objPos[ARRAY_MAX_CAP]; // Allocate new memory
    arrayCapacity = d.arrayCapacity;
    listSize = d.listSize;

    for (int i = 0; i < listSize; i++) {
        aList[i] = d.aList[i]; // Copy elements from the source
    }
}

// Copy Assignment Operator: Replaces the contents with those of another objPosArrayList.
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &d)
{
    if (this != &d) {
        // Clean up current list
        delete[] aList;

        // Allocate new memory and copy data
        aList = new objPos[ARRAY_MAX_CAP];
        arrayCapacity = d.arrayCapacity;
        listSize = d.listSize;

        for (int i = 0; i < listSize; i++) {
            aList[i] = d.aList[i];
        }
    }
    return *this;
}

// Get the current size of the list.
int objPosArrayList::getSize() const
{
    return listSize;
}

// Insert a new element at the head of the list.
void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize < ARRAY_MAX_CAP) {
        // Shift elements right to make room for the new head
        for (int i = listSize; i > 0; i--) {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos; // Insert new head
        listSize++;
    }
}

// Insert a new element at the tail of the list.
void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < ARRAY_MAX_CAP) {
        aList[listSize] = thisPos; // Add to the end
        listSize++;
    }
}

// Remove the head element from the list.
void objPosArrayList::removeHead()
{
    if (listSize > 0) {
        // Shift elements left to remove the head
        for (int i = 0; i < listSize - 1; i++) {
            aList[i] = aList[i + 1];
        }
        listSize--;
    }
}

// Remove the tail element from the list.
void objPosArrayList::removeTail()
{
    if (listSize > 0) {
        listSize--; // Decrease size to exclude the last element
    }
}

// Get the first element in the list.
objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

// Get the last element in the list.
objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

// Get the element at a specific index with bounds checking.
objPos objPosArrayList::getElement(int index) const
{
    if (index < 0) {
        index = 0; // Clamp to minimum index
    } else if (index >= listSize) {
        index = listSize - 1; // Clamp to maximum index
    }
    return aList[index];
}
