#include "World.h"
#include <iostream>
#include <tuple>
#include "CellType.h"
#include "Cell32Processer.h"

using namespace std;

World::World(unsigned int width, unsigned height) : width(width), height(height), ma(width, height)
{
	this->initialize();
}

int World::initialize()
{

	return 1;
}


World::~World() {
	cout << "World destructor" << endl;
}


void World::addCell(tuple<int, int> coordinates, CellType type, uint8_t clock, int addSize) {
	int x = get<0>(coordinates);
	int y = get<1>(coordinates);
	int x_even = 0;
	int y_even = 0;
	if (x < width && y < height) {
		for (int i = y; i < y + (addSize * 2); i++) {
			for (int j = x; j < x + (addSize * 2); j++) {
				if ((y_even % 2 == 0 && x_even % 2 == 0) || type == CellType::STONE) {
					if (j < width && i < height) {
						ma.set(i, j, type);
						c32p.awaken_neighbours(i, j, ma);
					}
				}
				x_even++;
			}
			y_even++;
		}
	}
}

MatrixApi* World::getMatrixApi() {
	return &ma;
}

void World::process(uint8_t clock)
{
	ma.reset();
	do {
		c32p.process(ma, clock);
	} while (ma.next() != -1);
}