#pragma once
#include <type_traits>
#include <iostream>

enum class CellType : uint8_t {
	AIR,
	SAND,
	WATER,
	STONE
};


template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
	return stream << static_cast<typename std::underlying_type<T>::type>(e);
}