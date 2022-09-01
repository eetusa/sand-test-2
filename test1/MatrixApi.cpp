#include "MatrixApi.h"
#include "Utility.h"
#include <iostream>

MatrixApi::MatrixApi(size_t width, size_t height) : width(width), height(height), size_(width * height)
{
	this->initialize();
}

/* 
Gets the cell where the iterator (read_location) is currently.
Returns: Cell32
*/
Cell32 MatrixApi::get()
{
	return cm[read_location];
}

/*
Gets the cell **relatively** by dx and dy from where the iterator (read_location) is currently.
Returns: Cell32
*/
std::optional<Cell32> MatrixApi::get(int dy, int dx) {
	int target = read_location + (width * dy) + dx;
	if (target >= 0 && target < size_) {
		return cm[target];
	}
	return std::nullopt;

}

/*
Set a cell in the current location of the iterator (read_location), overwriting existing cell.
Params: Cell32 cell
*/
void MatrixApi::set(Cell32 cell)
{
	cm[read_location] = cell;
}

/*
Set a cell in given coordinates, overwriting existing cell.
Params: int y, int x, CellType type
*/
void MatrixApi::set(int y, int x, CellType type) {
	if (y * x >= size_) return;
	cm[y * width + x] = Cell32{ type, 0, 0, 0 };
}

/*
Sets the cell **relatively** by dx and dy from where the iterator (read_location) is currently.
Paramas: int dy, int dx, Cell32 cell
*/
void MatrixApi::set(int dy, int dx, Cell32 cell) {
	int target = read_location + (width * dy) + dx;
	if (target >= 0 && target < size_) {
		cm[target] = cell;
		cm[target].clock = toggleClock(cm[target].clock);
	}
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

