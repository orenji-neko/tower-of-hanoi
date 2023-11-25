#include <iostream>
#include "raylib/raylib.h"
#include "tower.h"

int main(int argc, char **argv)
{
    Color colors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, VIOLET};
    int n = 7;

    InitWindow(800, 450, "tower of hanoi");

    Disk *selected = NULL;
    Tower *prev = NULL, *hovered = NULL;

    int x = 100;
    Tower *src = new Tower(x, 180, n);
    Tower *aux = new Tower((x * 2) + 90, 180, n);
    Tower *dest = new Tower((x * 3) + 180, 180, n);

    Stack<Tower*> *towers = new Stack<Tower*>(3);

    towers->push(src);
    towers->push(aux);
    towers->push(dest);

    for(int i = n; i > 0; i--)
    {
        src->push(new Disk(0, 0, 180 * i / n + 2, 20, colors[i - 1]));
    }

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        Vector2 mouseV = GetMousePosition();
        Vector2 mouseD = GetMouseDelta();

        for(int i = 0; i < 3; i++)
        {
            Tower *temp = towers->get(i);

            bool isSelectedEmpty = selected == NULL;
            bool onHover = CheckCollisionPointRec(mouseV, temp->getRectangle());

            // getting selected disk to selected pointer
            if(isSelectedEmpty && onHover && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
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
                hovered->push(selected);
                selected = NULL;
            }
            else
            {
                prev->push(selected);
                selected = NULL;
            }
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
            // drawing towers
            for(int i = 0; i < 3; i++)
            {
                towers->get(i)->draw();
            }
            // draw selected
            if(selected != NULL)
                selected->draw();
        EndDrawing();
    }

    CloseWindow();

    // memory deallocation
    while(!src->isEmpty())
        delete src->pop();
    while(!aux->isEmpty())
        delete aux->pop();
    while(!dest->isEmpty())
        delete dest->pop();
    delete src;
    delete aux;
    delete dest;

    return 0;
}