#pragma once
#include "stdint.h"
#include <iostream>

/*!
 * \class Color
 *
 * \brief A 4-component Color: RGBA.
 *
 */
class Color
{
public:
	Color() { r = 0; g = 0; b = 0; a = 0; }
	Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r(_r), g(_g), b(_b), a(_a) {}
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	inline friend std::ostream& operator<<(std::ostream& _os, const Color& _color) {
		_os << std::hex << "0x" << +_color.r << +_color.g << +_color.b << +_color.a;

		return _os;
	}
	bool operator==(const Color& _other) {
		return r == _other.r && g == _other.g && b == _other.b && a == _other.a;
	}
};

