#pragma once
#include "CellType.h"

struct Cell32 {
	CellType type;
	uint8_t ra;
	uint8_t rb;
	uint8_t clock;
};