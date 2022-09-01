#pragma once
#include <vector>
#include "Cell32.h"
using namespace std;
class MatrixApi
{
private:
	vector<Cell32> cm;
	size_t width;
	size_t height;
	unsigned int read_location = 0;
	size_t size_;

public:
	MatrixApi(size_t width, size_t height);

	Cell32 get();
	void set(Cell32 cell);
	int next();
	size_t size() const { return size_; }
	unsigned int getLocation() { return read_location; }
	void reset();
	vector<Cell32>* getMatrix() { return &cm; }
	void set(int y, int x, CellType type);

private:
	void  initialize();
};

