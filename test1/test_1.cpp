// g++ main.cpp `pkg-config --cflags --libs sdl2`
#include <SDL.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Game.h"




int main(int, char**)
{
    Game game = Game(600,600);
    game.do_something();
    
    game.run();

    return 0;
}