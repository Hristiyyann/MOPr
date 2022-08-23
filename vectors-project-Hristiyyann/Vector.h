#pragma once
#include "Point.h"
class Point;

class Vector {
	double x, y;
public:
	Vector(Point start, Point end);
	Vector(double x, double y) : x(x), y(y) {};
	double get_x();
	double get_y();
	void Multiply(Vector &for_multiply, double size);
};

