#pragma once
#include "Point.h"
class Line {
	double A, B, C;
public:
 	Line(double A = 0, double B = 0, double C = 0) : A(A), B(B), C(C) {}
	Line(const Point& p1, const Point& p2);
	double get_A();
	double get_B();
	double get_C();
	Line perpendicular(const Point& p);
};

