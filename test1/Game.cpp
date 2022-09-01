#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <vector>
#include <thread>
#include "Utility.h"

using namespace std;

Game::Game(unsigned int width, unsigned height) : width(width), height(height){
	this->initialize();
}



int Game::run() {
    // main loop
    int add_counter = 0;
    running = true;

    while (running)
    {
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            handleEvent(&ev);
        }

        if (leftMouseDown && add_counter == 0) {
            world->addCell(coordinatesToAdd, addType, clock, addSize);
            addToWorld = false;
            add_counter++;
        }
        if (add_counter > 0) {
            add_counter++;
            if (add_counter > 3) {
                add_counter = 0;
            }
        }

        world->process(clock);
        renderer->draw(world->getMatrixApi());

        clock = toggleClock(clock);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    end();

    return 0;
}

void Game::end() {
    delete renderer;
    delete world;
}


void Game::handleEvent(SDL_Event* e)
{
    //If mouse event happened

    if ((SDL_QUIT == e->type) ||
        (SDL_KEYDOWN == e->type && SDL_SCANCODE_ESCAPE == e->key.keysym.scancode))
    {
        running = false;
        return;
    }


    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        float log_x;
        float log_y;

        SDL_GetMouseState(&x, &y);
        SDL_RenderWindowToLogical(renderer->renderer, x, y, &log_x, &log_y);
        coordinatesToAdd = make_tuple( floor(log_x), floor(log_y) );

        //Set mouse over sprite
        switch (e->type)
        {
        case SDL_MOUSEBUTTONUP:
            if (e->button.button == SDL_BUTTON_LEFT) {
                leftMouseDown = false;
               
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            //  mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
            if (e->button.button == SDL_BUTTON_LEFT) {

                leftMouseDown = true;
                //const unsigned int offset = (this->width * y * 4) + x * 4;
               // (this->pixels)[offset + 0] = rand() % 256;        // b
                //(this->pixels)[offset + 1] = rand() % 256;        // g
                //(this->pixels)[offset + 2] = rand() % 256;        // r
                //(this->pixels)[offset + 3] = SDL_ALPHA_OPAQUE;    // a
                addToWorld = true;
            }
            break;

        case SDL_MOUSEMOTION:
            if (leftMouseDown == true) {
                //const unsigned int offset = (this->width * y * 4) + x * 4;
                //(this->pixels)[offset + 0] = rand() % 256;        // b
                //(this->pixels)[offset + 1] = rand() % 256;        // g
                //(this->pixels)[offset + 2] = rand() % 256;        // r
                //(this->pixels)[offset + 3] = SDL_ALPHA_OPAQUE;    // a
                addToWorld = true;
            }
            break;

        }
        return;
    }

    if (e->type == SDL_MOUSEWHEEL)
    {
        if (e->wheel.y > 0) // scroll up
        {
            addSize = addSize + 1;
        }
        else if (e->wheel.y < 0) // scroll down
        {
            addSize = addSize - 1;
            if (addSize <= 1) addSize = 1;
        }
        cout << "add size: " << addSize << endl;
        return;
    }

    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.scancode) {
            case SDL_SCANCODE_0:
                addType = static_cast<CellType>(0);
                break;
            case SDL_SCANCODE_1:
                addType = static_cast<CellType>(1);
                break;
            case SDL_SCANCODE_2:
                addType = static_cast<CellType>(2);
                break;
            case SDL_SCANCODE_3:
                addType = static_cast<CellType>(3);
                break;
        }
        cout << "Type to add: " << addType << endl;

    }

}

int Game::initialize() {
    this->leftMouseDown = false;
    this->updateTracker = false;
    this->addToWorld = false;

	cout << "Initializing Game" << endl;
    
    this->renderer = new Renderer(width, height);
    this->world = new World(width, height);

	return 1;
}
