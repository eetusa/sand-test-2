#include "Cell32Processer.h"
#include <iostream>
#include <random>
#include <optional>


void Cell32Processer::awaken_neighbours(int y, int x, MatrixApi& api)
{
	Neighbours neighbours;
	neighbours.add(1, 0, true);
	neighbours.add(1, -1, true);
	neighbours.add(1, 1, true);
	neighbours.add(0, 1, true);
	neighbours.add(0, -1, true);
	neighbours.add(-1, 0, true);


	for (int i = 0; i < neighbours.size(); i++) {
		int dy = y + neighbours.array[i].dy;
		int dx = x + neighbours.array[i].dx;
		bool only_awaken = neighbours.array[i].only_awaken;

		optional<Cell32> neighbour = api.getCellOptionalByCoordinates(dy, dx);

		if (neighbour) {

				if (neighbour->inactive) {

					if (dy == -1) {
						api.getCellReferenceByCoordinates(dy, dx)->inactive = false;
					}
					else {
						if (get_random(-1, 2) == -1) api.getCellReferenceByCoordinates(dy, dx)->inactive = false;
					}
				}
		}
	}

}

void Cell32Processer::process_sand(Cell32 cell, MatrixApi& api)
{
	int dx = get_random(-1, 1);
	Neighbours neighbours;
	neighbours.add(1, 0, false);
	if (dx != 0) neighbours.add(1, dx, false);
	neighbours.add(0, 1, true);
	neighbours.add(0, -1, true);
	neighbours.add(-1, 0, true);
	bool placed = false;

	for (int i = 0; i < neighbours.size(); i++) {
		int dy = neighbours.array[i].dy;
		int dx = neighbours.array[i].dx;
		bool only_awaken = neighbours.array[i].only_awaken;

		optional<Cell32> neighbour = api.getOptional(dy, dx);

		if (neighbour) {
			if (only_awaken || placed) {
				if (neighbour->inactive) {
					if (dy == -1) {
						api.getCellReference(dy, dx)->inactive = false;
					}
					else {
						if (get_random(-1, 2) == -1) api.getCellReference(dy, dx)->inactive = false;
					}
				}
				continue;
			}
			if (neighbour->type == CellType::AIR) {
				api.set(0, 0, Cell32{ CellType::AIR, 0,0,0 });
				api.set(1, dx, cell);
				placed = true;
				continue;
			}
			else if (neighbour->type == CellType::WATER) {


			}
		}
	}

	if (get_random(-1, 3) > 0) api.getCellReference()->inactive = true;
}

void Cell32Processer::process_water(Cell32 cell, MatrixApi& api)
{
	//todo
}

void Cell32Processer::process(MatrixApi& api, uint8_t clock)
{
	Cell32* cell = api.getCellReference();
	if (cell->clock == clock || cell->inactive) return;

	CellType type = cell->type;

	switch (type) {
		case CellType::AIR:
			//
			break;
		case CellType::SAND:
			process_sand(*cell, api);
			break;
		case CellType::STONE:
			//
			break;
		case CellType::WATER:
			process_water(*cell, api);
			break;
	}
}

int Cell32Processer::get_random(int lower, int upper) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(lower, upper);
	return distr(gen);
}