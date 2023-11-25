#include <iostream>

#include "raylib/raylib.h"
#include "tower.h"

int main(int argc, char **argv)
{
    InitWindow(800, 450, "tower of hanoi");
    MainScene *mainscene = new MainScene(3);

    int code;
    bool state = true;

    SetTargetFPS(60);
    while(!WindowShouldClose() && state)
    {
        code = mainscene->Update();

        BeginDrawing();
            ClearBackground(BLACK);
            mainscene->Draw();
        EndDrawing();

        switch(code)
        {
        case -1:
            state = false;
            break;
        }
    }

    delete mainscene;

    CloseWindow();

    return 0;
}