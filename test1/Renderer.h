#pragma once
#include <SDL.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>
#include "MatrixApi.h"

class Renderer
{
	SDL_Window* window;
	SDL_RendererInfo info;
	const unsigned int width;
	const unsigned int height;
	SDL_Texture* texture;
	std::vector< unsigned char > pixels;

public:
	Renderer(unsigned int width, unsigned int height);
	~Renderer();
	SDL_Renderer* renderer;
	void draw(MatrixApi* ma);

private:
	int initialize();
	void PrintFrameTiming(std::ostream& os = std::cout, float period = 2.0f);
	void matrixApiToPixels(MatrixApi* ma);
};

