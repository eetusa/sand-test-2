#pragma once
#include <tuple>
#include "CellType.h"
#include "MatrixApi.h"
#include "Cell32Processer.h"

using namespace std;

class World
{
	const unsigned int width;
	const unsigned int height;
	
	MatrixApi ma;
	Cell32Processer c32p;

public:
	World(unsigned int width, unsigned height);
	~World();

	void process(uint8_t clock);
	MatrixApi* getMatrixApi();
	void addCell(tuple<int, int> coordinates, CellType type, uint8_t clock, int addSize);

private:
	int initialize();
};

