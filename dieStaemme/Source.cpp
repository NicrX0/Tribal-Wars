#include <iostream>
#include "Game.h"
#include "Framework.h"


int main(int argc, char* args[])
{
    if (!g_pFramework->Init(1920.0f, 1080.0f)) //Set aspect ratio here
    {
        printf("Error, failed to initialize Framework!\n");
    }

    //Game
    Game game;
    game.Initialize(g_pFramework->GetRenderer());
    game.Run();
    game.Quit();

    g_pFramework->Quit();
    g_pFramework->Del();

    return 0;
}