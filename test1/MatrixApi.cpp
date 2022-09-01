#include "MatrixApi.h"

MatrixApi::MatrixApi(size_t width, size_t height) : width(width), height(height), size_(width * height)
{
	this->initialize();
}

Cell32 MatrixApi::get()
{
	return cm[read_location];
}

void MatrixApi::set(Cell32 cell)
{
	cm[read_location] = cell;
}

int MatrixApi::next()
{
	this->read_location++;
	if (read_location < size_) return 1;
	else return -1;
}

void MatrixApi::initialize()
{
	for (int i = 0; i < width * height; i++) {
		cm.push_back(Cell32{
				CellType::AIR, 0, 0, 0
			});
	}
}


void MatrixApi::reset() {
	this->read_location = 0;
}

void MatrixApi::set(int y, int x, CellType type) {
	if (y * x >= size_) return;
	cm[y * width + x] = Cell32{type, 0, 0, 0};
}