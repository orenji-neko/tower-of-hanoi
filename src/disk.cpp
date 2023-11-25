#include <iostream>

#include "raylib/raylib.h"
#include "tower.h"

Disk::Disk(int x, int y, float width, float height, Color col)
{
    position = new Vector2{(float)x, (float)y};
    rect = new Rectangle{position->x - (width / 2), position->y, width, height};

    this->col = col;
}
    
Disk::~Disk()
{
    delete position;
    delete rect;
}

void Disk::setPosition(int x, int y)
{
    position->x = x;
    position->y = y;

    rect->x = position->x - rect->width / 2;
    rect->y = position->y;
}

void Disk::draw()
{
    DrawRectangleRec(*rect, col);
}

Rectangle Disk::getRectangle()
{
    return *rect;
}

Color Disk::getColor()
{
    return col;
}

Vector2 Disk::getPosition()
{
    return *position;
}