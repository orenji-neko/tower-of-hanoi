#include <iostream>
#include "raylib/raylib.h"
#include "tower.h"

int main(int argc, char **argv)
{
    InitWindow(800, 450, "tower of hanoi");
    
    // Ako'y nagbuhat ani. Dili ni siya daan gibuhat sa C++.
    Stack<Disk*> *stack = new Stack<Disk*>(5);
    Disk *selected = NULL;

    stack->push(new Disk(0, 0, 60, 60, YELLOW));
    stack->push(new Disk(10, 10, 60, 60, GREEN));

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        std::cout << stack->getLength() << std::endl;

        Vector2 mouseV = GetMousePosition();
        Vector2 mouseD = GetMouseDelta();

        // moving selected disk
        if(selected != NULL && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            int vx = selected->getPosition().x + mouseD.x;
            int vy = selected->getPosition().y + mouseD.y;

            selected->setPosition(vx, vy);
        }
        else if(selected != NULL)
        {
            stack->push(selected);
            selected = NULL;
        }

        // selecting disks
        for(int i = 0; i < stack->getLength(); i++)
        {
            if(selected == NULL && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouseV, stack->get(i)->getRectangle()))
                selected = stack->remove(i);
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
            // drawing disks
            for(int i = 0; i < stack->getLength(); i++)
                stack->get(i)->draw();
            // drawing selected
            if(selected != NULL)
                selected->draw();
        EndDrawing();
    }

    CloseWindow();
    delete stack;

    return 0;
}