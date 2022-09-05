#pragma once
#include "MatrixApi.h"
#include "Cell32.h"
#include "CellType.h"
#include <vector>

class Cell32Processer
{
private:
	struct Neighbour {
		int8_t dy;
		int8_t dx;
		bool only_awaken;
	};

	struct Neighbours {
		std::vector<Neighbour> array;
		void add(int8_t dy, int8_t dx, bool only_awaken) {
			array.push_back(Neighbour{dy, dx, only_awaken});
		}
		int size() {
			return array.size();
		}
	};

	void process_sand(Cell32 cell, MatrixApi& api);
	void process_water(Cell32 cell, MatrixApi& api);
	int get_random(int lower, int upper);

public:
	Cell32Processer() {};
	
	void process(MatrixApi& api, uint8_t clock);
	void awaken_neighbours(int y, int x, MatrixApi& api);

};

