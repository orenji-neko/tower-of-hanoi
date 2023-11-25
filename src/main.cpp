#include <iostream>
#include <string>
#include <cmath>
#include "raylib/raylib.h"
#include "tower.h"

int main(int argc, char **argv)
{
    InitWindow(800, 450, "tower of hanoi");
    MainScene *mainscene = new MainScene(3);

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        mainscene->Update();

        BeginDrawing();
            ClearBackground(BLACK);
            mainscene->Draw();
        EndDrawing();
    }

    delete mainscene;

    CloseWindow();

    return 0;
}