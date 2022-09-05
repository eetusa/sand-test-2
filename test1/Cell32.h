#pragma once
#include "CellType.h"

//struct Cell32 {
//	CellType type;	// type 8 bits
//	uint8_t ra;		// 4 bits color variance, 4 bits static
//	uint8_t rb;		// ?? ??
//	uint8_t clock;	// clock 8 bits
//};	

typedef  struct Cell32 {
	CellType type;
	uint8_t color : 4;
	uint8_t inactive : 4;
	uint8_t ra : 4;
	uint8_t rb : 4;
	uint8_t clock;
};