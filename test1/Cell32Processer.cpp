#include "Cell32Processer.h"
#include <iostream>

void Cell32Processer::process_sand(Cell32 cell, MatrixApi& api)
{
	//todo
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
