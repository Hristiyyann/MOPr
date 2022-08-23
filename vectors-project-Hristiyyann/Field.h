#pragma once

#include "Ball.h"
#include "Point.h"
#include "Line.h"
#include <vector>
#include <map>

class Point;

class Field {
	Ball ball;
	Point startingPoint;
	Point endPoints[4];
	Point endPointsAfterDiameter[4];
	vector<Line> wall_lines;
public:
	Field();
	Field(Point origin, double width, double height, Ball ball);
	Field(Point endPoints[4], Ball ball);
	void make_wall_lines();
	bool is_point_in_table(Point& for_check);
	map<int, Point> which_wall_crossing(Line dl, Point start, Point end);
	double find_mirror_x(double x_hit, Point end_point);
	double find_mirror_y(double y_hit, Point end_point);
	Point mirror_point(Line wall, Line perpendicular, Point end_point);
 	void hit(Point target, double power);

	friend ostream& operator<<(ostream& os, const Field& f);
	friend void ballCase(Field& f);

};

void simpleCase(Field& f);
void complexCase(Field& f);

