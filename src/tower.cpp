#include <iostream>

#include "raylib/raylib.h"
#include "tower.h"

Tower::Tower(int x, int y, int cap)
{
    position = new Vector2{x, y};
    rect = new Rectangle{position->x, position->y, 180, 200};
    tower = new Stack<Disk*>(cap);
}
Tower::~Tower()
{
    delete position;
    delete rect;
    delete tower;
}
void Tower::draw()
{
    // pole
    float poleWidth = 20;
    DrawRectangle(position->x + (rect->width / 2) - (poleWidth / 2), position->y, poleWidth, rect->height, WHITE);

    for(int i = 0; i < tower->getLength(); i++)
        tower->get(i)->draw();

    // base
    DrawRectangle(position->x, position->y + rect->height, rect->width, 20, WHITE); 
    // bounds
    //DrawRectangleLinesEx(*rect, 1.0f, RED);
}

void Tower::push(Disk *disk)
{
    disk->setPosition(position->x + rect->width/2, (position->y + rect->height - 18) - (20 * tower->getLength() + 1));
    tower->push(disk);
}

Disk* Tower::pop()
{
    return tower->pop();
}

Disk Tower::top()
{
    return *tower->top();
}

bool Tower::isEmpty()
{
    return tower->isEmpty();
}

Disk* Tower::popTopDiskOnHover(Vector2 mouseV)
{
    for(int i = 0; i < tower->getLength(); i++)
        if(CheckCollisionPointRec(mouseV, tower->get(i)->getRectangle()) && tower->get(i) == tower->top())
            return tower->pop();

    return NULL;
}

Rectangle Tower::getRect()
{
    return *rect;
}