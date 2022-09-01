#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include "Renderer.h"
#include "World.h"
#include "CellType.h"

using namespace std;

class Game {

private:
	Renderer* renderer;
	World* world;

	const unsigned int width;
	const unsigned int height;

	bool leftMouseDown;
	bool updateTracker;
	bool running;

	bool addToWorld;
	int addSize = 1;
	tuple <int, int> coordinatesToAdd;
	CellType addType = CellType::SAND;

	uint8_t clock = 0;
	void toggleClock();

public:
	Game(unsigned int width, unsigned int height);
	int run();

private:
	int initialize();
	void handleEvent(SDL_Event* e);
	void end();
};