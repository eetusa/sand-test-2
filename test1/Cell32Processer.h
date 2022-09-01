#pragma once
#include "MatrixApi.h"
#include "Cell32.h"
#include "CellType.h"

class Cell32Processer
{
private:
	void process_sand(Cell32 cell, MatrixApi& api);
	void process_water(Cell32 cell, MatrixApi& api);

public:
	Cell32Processer() {};
	
	void process(MatrixApi& api, uint8_t clock);
};

