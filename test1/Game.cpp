#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

Game::Game(unsigned int width, unsigned height) : width(width), height(height), pixels(width * height * 4, 0){
	this->initialize();
}


int Game::run() {
    bool useLocktexture = false;

    // main loop
    bool running = true;
    while (running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // handle events
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            if ((SDL_QUIT == ev.type) ||
                (SDL_KEYDOWN == ev.type && SDL_SCANCODE_ESCAPE == ev.key.keysym.scancode))
            {
                running = false;
                break;
            }

            if (SDL_KEYDOWN == ev.type && SDL_SCANCODE_L == ev.key.keysym.scancode)
            {
                useLocktexture = !useLocktexture;
                std::cout << "Using " << (useLocktexture ? "SDL_LockTexture() + std::copy_n()" : "SDL_UpdateTexture()") << '\n';
            }
            if (SDL_MOUSEBUTTONDOWN == ev.type || SDL_MOUSEMOTION == ev.type || SDL_MOUSEBUTTONUP == ev.type) {
                handleEvent(&ev);
            }

        }

        if (useLocktexture)
        {
            unsigned char* lockedPixels = nullptr;
            int pitch = 0;
            SDL_LockTexture(texture, nullptr, reinterpret_cast<void**>(&lockedPixels), &pitch);
            std::copy_n(pixels.data(), pixels.size(), lockedPixels);
            SDL_UnlockTexture(texture);
        }
        else
        {
            SDL_UpdateTexture(texture, nullptr, pixels.data(), this->width * 4);
        }

        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;



}


void Game::handleEvent(SDL_Event* e)
{
    //If mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
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
                const unsigned int offset = (this->width * y * 4) + x * 4;
                (this->pixels)[offset + 0] = rand() % 256;        // b
                (this->pixels)[offset + 1] = rand() % 256;        // g
                (this->pixels)[offset + 2] = rand() % 256;        // r
                (this->pixels)[offset + 3] = SDL_ALPHA_OPAQUE;    // a
            }
            break;

        case SDL_MOUSEMOTION:
            if (leftMouseDown == true) {
                const unsigned int offset = (this->width * y * 4) + x * 4;
                (this->pixels)[offset + 0] = rand() % 256;        // b
                (this->pixels)[offset + 1] = rand() % 256;        // g
                (this->pixels)[offset + 2] = rand() % 256;        // r
                (this->pixels)[offset + 3] = SDL_ALPHA_OPAQUE;    // a
            }
            break;

        }

    }
}

void Game::do_something() {
	cout << "Testing!" << endl;
}


int Game::initialize() {
    this->leftMouseDown = false;
    cout << pixels.size() << endl;
	cout << "Initializing Game" << endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    this->window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_GetRendererInfo(renderer, &info);

    std::cout << "Renderer name: " << info.name << '\n';
    std::cout << "Texture formats: " << '\n';
    for (Uint32 i = 0; i < info.num_texture_formats; i++)
    {
        std::cout << SDL_GetPixelFormatName(info.texture_formats[i]) << '\n';
    }

    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, this->width, this->height);
    //this->pixels(width * height * 4, 0);

	return 1;
}

void Game::PrintFrameTiming(std::ostream& os, float period)
{
    static unsigned int frames = 0;
    frames++;
    static auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    float seconds = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
    if (seconds > period)
    {
        float spf = seconds / frames;
        os
            << frames << " frames in "
            << std::setprecision(1) << std::fixed << seconds << " seconds = "
            << std::setprecision(1) << std::fixed << 1.0f / spf << " FPS ("
            << std::setprecision(3) << std::fixed << spf * 1000.0f << " ms/frame)\n";
        frames = 0;
        start = end;
    }
}

