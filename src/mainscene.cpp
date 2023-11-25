#include <iostream>
#include <string>
#include <cmath>

#include "raylib/raylib.h"
#include "tower.h"

MainScene::MainScene(int n)
{
    this->n = n;
    count = 0;
    moves = pow(2, n) - 1;

    hasWon = false;

    selected = NULL;
    prev = NULL;
    hovered = NULL;

    int x = 100;
    src = new Tower(x, 180, n);
    aux = new Tower((x * 2) + 90, 180, n);
    dest = new Tower((x * 3) + 180, 180, n);

    towers = new Stack<Tower*>(3);

    towers->push(src);
    towers->push(aux);
    towers->push(dest);

    // filling up the source
    for(int i = n; i > 0; i--)
    {
        src->push(new Disk(0, 0, 180 * i / n + 2, 20, this->getColor(i - 1)));
    }

}

int MainScene::Update()
{
    Vector2 mouseV = GetMousePosition();
    Vector2 mouseD = GetMouseDelta();

    // reset key
    if(IsKeyPressed(KEY_R))
        reset();

    // checking each tower and its disks
    for(int i = 0; i < 3; i++)
    {
        Tower *temp = towers->get(i);

        bool isSelectedEmpty = selected == NULL;
        bool onHover = CheckCollisionPointRec(mouseV, temp->getRectangle());

        // getting selected disk to selected pointer
        if(isSelectedEmpty && onHover && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !hasWon)
        {
            selected = temp->popTopDiskOnHover(mouseV);
            prev = temp;
        }
        // getting hovered tower reference
        if(onHover)
            hovered = temp;
    }

    // controlling selected disk
    if(selected != NULL && prev != NULL && hovered != NULL)
    {
        // holding down left click
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            int nx = selected->getPosition().x + mouseD.x;
            int ny = selected->getPosition().y + mouseD.y;
            selected->setPosition(nx, ny);
        }
        // released left click on tower area
        else if(hovered->isEmpty() || (!hovered->isEmpty() && hovered->top()->getRectangle().width > selected->getRectangle().width))
        {
            count++;
            hovered->push(selected);
            selected = NULL;
        }
        // if can't push to tower
        else
        {
            prev->push(selected);
            selected = NULL;
        }
    }

    // win check
    hasWon = dest->getLength() >= n;

    return 0;
}

void MainScene::Draw()
{
    // drawing towers
    for(int i = 0; i < 3; i++)
    {
        towers->get(i)->draw();
    }

    // draw selected
    if(selected != NULL)
        selected->draw();
    // text

    // disk amount manipulator
    DrawText(("Disks: " + std::to_string(n)).c_str(), 10, 10, 16, WHITE);

    // move counter
    Color c = hasWon ? GREEN : WHITE;
    DrawText(("Moves: " + std::to_string(count) + "/" + std::to_string(moves)).c_str(), 80, 10, 16, c);

    // controls
    DrawText("[R] Reset [ESC] Exit", 10, 430, 16, RAYWHITE);
}

MainScene::~MainScene()
{
    // deallocating disks
    for(int i = 0; i < 3; i++)
    {
        Tower *tmp = towers->get(i);
        while(!tmp->isEmpty())
            delete tmp->pop();
    }

    // pointer to null
    selected = NULL;
    prev = NULL;
    hovered = NULL;

    // sige pinapalaya na kita
    delete src;
    delete aux;
    delete dest;
}

Color MainScene::getColor(int index)
{
    Color colors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, VIOLET};
    return colors[index];
}

void MainScene::reset()
{
    // deallocating disks in all 3 towers
    for(int i = 0; i < 3; i++)
    {
        Tower *tmp = towers->get(i);
        while(!tmp->isEmpty())
            delete tmp->pop();
    }

    // refilling source
    for(int i = n; i > 0; i--)
    {
        src->push(new Disk(0, 0, 180 * i / n + 2, 20, this->getColor(i - 1)));
    }

    count = 0;
    moves = pow(2, n) - 1;
}