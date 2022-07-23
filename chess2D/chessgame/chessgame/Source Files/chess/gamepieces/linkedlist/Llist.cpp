#include "Llist.h"
#include <iostream>

Llist::Llist(){this->head = NULL; this->listSize = 0;}

Llist::~Llist()
{
    if(this->head == NULL || this->listSize == 0)return;

    XYcoords* nodePtr = this->head;
    XYcoords* nextNode;

    while(nodePtr != NULL)
    {
        nextNode = nodePtr->next;
        delete nodePtr;
        nodePtr = NULL;
        nodePtr = nextNode;
    }
    this->head = NULL;
}

int Llist::size(){return this->listSize;}

XYcoords* Llist::gethead(){return this->head;}

void Llist::push_back(XYcoords newData)
{
    XYcoords* newNode = new XYcoords;
    newNode->x = newData.x;
    newNode->y = newData.y;
    newNode->next = NULL;

    if(this->head == NULL)this->head = newNode;
    else
    {
        XYcoords* nodePtr = this->head;

        while(nodePtr->next != NULL)nodePtr = nodePtr->next;

        nodePtr->next = newNode;
    }
    ++this->listSize;
}

void Llist::push_back(XYcoords newData, XYcoords* currentNode)
{
    if(this->listSize == 0 || currentNode->next == NULL)
    {
        XYcoords* newNode = new XYcoords;
        newNode->x = newData.x;
        newNode->y = newData.y;
        newNode->next = NULL;
        if(this->listSize == 0)this->head = newNode;
        else if(currentNode->next == NULL)currentNode->next = newNode;
        ++this->listSize;
        return;
    }
    this->push_back(newData, currentNode->next);
}

void Llist::clearList()
{
    if(this->head == NULL)return;

    XYcoords* nodePtr = this->head;
    XYcoords* nextNode;

    while(nodePtr != NULL)
    {
        nextNode = nodePtr->next;
        delete nodePtr;
        nodePtr = NULL;
        nodePtr = nextNode;
    }
    this->head = NULL;
    this->listSize = 0;
}

void Llist::clearList(XYcoords* currentNode)
{
    if(currentNode == NULL)return;

    this->clearList(currentNode->next);
    delete currentNode;
    currentNode = NULL;
    --this->listSize;
}

std::vector<XYpos> Llist::getOpenPositionsVec()
{
    std::vector<XYpos> vect;

    if(this->head == NULL)return vect;

    XYcoords* nodePtr = this->head;

    while(nodePtr != NULL)
    {
        XYpos element;
        element.x = nodePtr->x;
        element.y = nodePtr->y;
        vect.push_back(element);
        nodePtr = nodePtr->next;
    }
    this->clearList();

    return vect;
}