#pragma once
#include "MatrixApi.h"
#include "Cell32.h"
#include "CellType.h"
#include <vector>

class Cell32Processer
{
private:
	struct Neighbours {
		std::vector<std::vector<int>> array;
		void add(int dy, int dx) {
			array.push_back(std::vector<int>{dy, dx});
		}
		int size() {
			return array.size();
		}
	};
	void process_sand(Cell32 cell, MatrixApi& api);
	void process_water(Cell32 cell, MatrixApi& api);
	int get_random();

public:
	Cell32Processer() {};
	
	void process(MatrixApi& api, uint8_t clock);
};

