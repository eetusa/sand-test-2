#pragma once
#include <vector>
#include "Cell32.h"
#include <optional>

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
	vector<Cell32>* getMatrix() { return &cm; }

	Cell32 get();
	optional<Cell32> getOptional(int dy, int dx);
	optional<Cell32> getCellOptionalByCoordinates(int y, int x);
	Cell32* getCellReference() { return &cm[read_location]; };
	Cell32* getCellReference(int dy, int dx);
	Cell32* getCellReferenceByCoordinates(int y, int x);
	

	size_t size() const { return size_; }
	unsigned int getLocation() { return read_location; }

	int next();
	void reset();

	void set(Cell32 cell);
	void set(int y, int x, CellType type);
	void set(int dy, int dx, Cell32 cell);

private:
	void  initialize();
};

