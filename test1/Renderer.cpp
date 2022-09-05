#include "Renderer.h"
#include <SDL.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;



//void Renderer::draw(std::vector<unsigned char>* pixels)
//{
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//    SDL_RenderClear(renderer);
//
// /*   if (useLocktexture)
//    {
//        unsigned char* lockedPixels = nullptr;
//        int pitch = 0;
//        SDL_LockTexture(texture, nullptr, reinterpret_cast<void**>(&lockedPixels), &pitch);
//        std::copy_n(pixels.data(), pixels.size(), lockedPixels);
//        SDL_UnlockTexture(texture);
//    }
//    else*/
//    //{
//    SDL_UpdateTexture(texture, nullptr, (*pixels).data(), this->width * 4);
//    //}
//
//    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
//    SDL_RenderPresent(renderer);
//}

Renderer::Renderer(unsigned int width, unsigned int height) : width(width), height(height), pixels(width* height * 4, 0)
{
    this->initialize();
}




void Renderer::draw(MatrixApi* ma)
{
    matrixApiToPixels(ma);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_UpdateTexture(texture, nullptr, pixels.data(), this->width * 4);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}


void Renderer::matrixApiToPixels(MatrixApi* ma)
{

    ma->reset();
    do {
        Cell32* cell = ma->getCellReference();
        CellType type = cell->type;

        int r = 0;
        int g = 0;
        int b = 0;

        if (type == CellType::SAND) {
            r = 239, g = 239, b = 29;
        }

        if (type == CellType::WATER) {
            r = 0, g = 100, b = 200;
        }

        if (type == CellType::STONE) {
            r = 150, g = 150, b = 150;
        }

        const unsigned int offset = ma->getLocation()*4;
        (this->pixels)[offset + 0] = b;        // b
        (this->pixels)[offset + 1] = g;        // g
        (this->pixels)[offset + 2] = r;        // r
        (this->pixels)[offset + 3] = SDL_ALPHA_OPAQUE;    // a

    } while (ma->next() != -1);
}

int Renderer::initialize() {
    cout << "Initializing Renderer" << endl;
    SDL_Init(SDL_INIT_EVERYTHING);

    this->window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_RESIZABLE);
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_RenderSetLogicalSize(renderer, width, height);
    SDL_GetRendererInfo(renderer, &info);

    std::cout << "Renderer name: " << info.name << '\n';
    std::cout << "Texture formats: " << '\n';
    for (Uint32 i = 0; i < info.num_texture_formats; i++)
    {
        std::cout << SDL_GetPixelFormatName(info.texture_formats[i]) << '\n';
    }

    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, this->width, this->height);

    return 1;
}

void Renderer::PrintFrameTiming(std::ostream& os, float period)
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



Renderer::~Renderer()
{
    cout << "Renderer destructor" << endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
