#include <iostream>

#include "raylib/raylib.h"
#include "tower.h"

int main(int argc, char **argv)
{
    std::cout << "How many disks[3-7]? ";
    int n;
    std::cin >> n;

    if(n > 7 || n < 3)
    {
        std::cerr << "Invalid amount!" << std::endl;
        return -1;
    }

    InitWindow(800, 450, "tower of hanoi");

    MainScene *mainscene = new MainScene(n);

    int code = 0;
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

    CloseWindow();

    delete mainscene;

    return 0;
}