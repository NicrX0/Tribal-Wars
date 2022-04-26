#include <iostream>
#include "Game.h"
#include "Framework.h"


int main(int argc, char* args[])
{
    /*int z1, z2, z3;
    int temp;
    std::cout << "Zahl 1: ";
    std::cin >> z1;
    std::cout << std::endl;
    std::cout << "Zahl 2: ";
    std::cin >> z2;
    std::cout << std::endl;
    std::cout << "Zahl 3: ";
    std::cin >> z3;
    std::cout << std::endl;
    test2 test3
    temp = z1 / z2;
    std::cout << "Ergebnis: " << temp << std::endl;
    */
    if (!g_pFramework->Init(800.0f, 600.0f)) //Set aspect ratio here
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