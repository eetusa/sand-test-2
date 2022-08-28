#pragma once
#include <SDL.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>

class Game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_RendererInfo info;
	const unsigned int width;
	const unsigned int height;
	SDL_Texture* texture;
	std::vector< unsigned char > pixels;
	bool leftMouseDown;

public:
	Game(unsigned int width, unsigned int height);
	void do_something();
	int run();

private:
	int initialize();
	void PrintFrameTiming(std::ostream& os = std::cout, float preiod = 2.0f);
	void handleEvent(SDL_Event* e);
};