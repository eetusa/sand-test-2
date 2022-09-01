#include "Cell32Processer.h"
#include <iostream>
#include <random>
#include <optional>


void Cell32Processer::process_sand(Cell32 cell, MatrixApi& api)
{
	int dx = get_random();
	Neighbours neighbours;
	neighbours.add(1, 0);
	neighbours.add(1, dx);

	for (int i = 0; i < neighbours.size(); i++) {
		int dy = neighbours.array[i][0];
		int dx = neighbours.array[i][1];
		optional<Cell32> neighbour = api.get(dy, dx);

		if (neighbour) {
			if (neighbour->type == CellType::AIR) {
				api.set(0, 0, Cell32{ CellType::AIR, 0,0,0 });
				api.set(1, dx, cell);
				return;
			}
			else if (neighbour->type == CellType::WATER) {


			}
		}
	}
}

void Cell32Processer::process_water(Cell32 cell, MatrixApi& api)
{
	//todo
}

void Cell32Processer::process(MatrixApi& api, uint8_t clock)
{
	Cell32 cell = api.get();
	if (cell.clock == clock) return;

	CellType type = cell.type;

	switch (type) {
		case CellType::AIR:
			//
			break;
		case CellType::SAND:
			process_sand(cell, api);
			break;
		case CellType::STONE:
			//
			break;
		case CellType::WATER:
			process_water(cell, api);
			break;
	}
}

int Cell32Processer::get_random() {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(-1, 1);
	return distr(gen);
}