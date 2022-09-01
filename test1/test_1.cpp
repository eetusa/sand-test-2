// g++ main.cpp `pkg-config --cflags --libs sdl2`
#include <SDL.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Game.h"
#include <bitset>

#include "Cell32Processer.h"
#include "MatrixApi.h"

#include <random>



int main(int, char**)
{
    Game game = Game(200,200);
    game.run();

    return 0;
}