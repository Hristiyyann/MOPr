#include "Field.h"
#include "Line.h"
#include "Point.h"
#include "Vector.h"
#include <cmath>
#include <map>

bool is_power_valid(double power)
{
	if(power < 1 || power > 10)
	{
		return false;
	}
	
	return true;
}

bool is_valid_ground(double width, double height)
{
	if(width == (height * 2))
	{
		return true;
	}
	
	return false;
}

bool is_equal(Point &p1, Point &p2) // Функция, която проверява дали кординатите на 2 точки са равни. 
{
	if ((p1.x == p2.x) && (p1.y == p2.y))
	{
		return true;
	}
	return false;
}

bool is_in_any_angle(Point endpoints[4], Point& for_check) // Функция, която проверява дали точката на засичане на две прави не е в някой от ъглите на масата.
{
	for(int i = 0; i < 4; i++)
	{
		if(is_equal(endpoints[i], for_check))
		{
			return true;
		}
	}
	return false;
}

Point initiliaze_point(Point &p) // Функция, която инициализира стойностите от една точка на друга.
{
	return Point(p.x, p.y);
}

Point find_point(Vector &point, Point start) // Функция, която намира от вектор и начална точка - крайната точка.
{
	Point end_point;
	end_point.x = start.x - point.get_x();
	end_point.y = start.y - point.get_y();
	return end_point;
}

Field::Field() {}

Field::Field(Point origin, double width, double height, Ball ball)
{
	while(!is_valid_ground(width, height))
	{
		cout << "These aren't valid ground points! Write new ones"<< endl;
		cin >> width;
		cin >> height;
	}

	endPoints[0] = Point(origin.x, origin.y);
	endPoints[1] = Point(origin.x + width, origin.y);
	endPoints[2] = Point(origin.x + width, origin.y + height);
	endPoints[3] = Point(origin.x, origin.y + height);

	this->ball = ball;
	this->startingPoint = ball.center;

	endPointsAfterDiameter[0] = Point(origin.x + ball.diameter / 2, origin.y + ball.diameter / 2);
	endPointsAfterDiameter[1] = Point(origin.x + width - ball.diameter / 2, origin.y + ball.diameter / 2);
	endPointsAfterDiameter[2] = Point(origin.x + width - ball.diameter / 2, origin.y + height - ball.diameter / 2);
	endPointsAfterDiameter[3] = Point(origin.x + ball.diameter / 2, origin.y + height - ball.diameter / 2);
}

Field::Field(Point endPoints[4], Ball ball)
{
	// Изнасям пресмятането на дължината и ширината най-отгоре, за да може да проверя дали полето е валидно преди да съм инициализирал точките.
	double length_AB = sqrt(pow(endPoints[1].x - endPoints[0].x, 2) + pow(endPoints[1].y - endPoints[0].y, 2));
	double length_AD = sqrt(pow(endPoints[3].x - endPoints[0].x, 2) + pow(endPoints[3].y - endPoints[0].y, 2));

	while(!is_valid_ground(length_AB, length_AD))
	{
		cout << "These aren't valid ground points! Write new ones"<< endl;
		for(int i = 0; i < 4; i++)
		{
			cin >> endPoints[i];
		}
		length_AB = sqrt(pow(endPoints[1].x - endPoints[0].x, 2) + pow(endPoints[1].y - endPoints[0].y, 2));
	    length_AD = sqrt(pow(endPoints[3].x - endPoints[0].x, 2) + pow(endPoints[3].y - endPoints[0].y, 2));
	}
	
	for (int i = 0; i < 4; ++i)
	{
		this->endPoints[i] = endPoints[i];
		endPointsAfterDiameter[i] = endPoints[i];
	}


	Vector AB(endPoints[0], endPoints[1]);
	Vector AD(endPoints[0], endPoints[3]);
	Vector AB_radius = AB, AD_radius = AD;

	AB.Multiply(AB_radius, (ball.diameter / 2) / length_AB);
	AD.Multiply(AD_radius, (ball.diameter / 2) / length_AD);

	Vector opposite_AB_radius(-AB_radius.get_x(), -AB_radius.get_y());
	Vector opposite_AD_radius(-AD_radius.get_x(), -AD_radius.get_y());

	
	Point point_prim = find_point(AD_radius, endPoints[0]);
	Point new_A = find_point(AB_radius, point_prim);
	endPointsAfterDiameter[0] = new_A;

	point_prim = find_point(AD_radius, endPoints[1]);
	Point new_B = find_point(opposite_AB_radius, point_prim);
	endPointsAfterDiameter[1] = new_B;

	point_prim = find_point(opposite_AD_radius, endPoints[2]);
	Point new_C = find_point(opposite_AB_radius, point_prim);
	endPointsAfterDiameter[2] = new_C;

	point_prim = find_point(opposite_AD_radius, endPoints[3]);
	Point new_D = find_point(AB_radius, point_prim);
	endPointsAfterDiameter[3] = new_D;

	this->ball = ball;
	this->startingPoint = ball.center;
}

void Field::make_wall_lines() // Функция, която прави прави между всеки две точки на масата
{
	wall_lines.push_back(Line(endPointsAfterDiameter[0], endPointsAfterDiameter[1]));
	wall_lines.push_back(Line(endPointsAfterDiameter[1], endPointsAfterDiameter[2]));
	wall_lines.push_back(Line(endPointsAfterDiameter[2], endPointsAfterDiameter[3]));
	wall_lines.push_back(Line(endPointsAfterDiameter[3], endPointsAfterDiameter[0]));
}

bool Field::is_point_in_table(Point &for_check) // Функция, която проверява дали дадена точка е в полето или извън него.
{
	double area_table = 0;
	double width = sqrt(pow(endPointsAfterDiameter[1].x - endPointsAfterDiameter[0].x, 2) + pow(endPointsAfterDiameter[1].y - endPointsAfterDiameter[0].y, 2));
	double height = sqrt(pow(endPointsAfterDiameter[3].x - endPointsAfterDiameter[0].x, 2) + pow(endPointsAfterDiameter[3].y - endPointsAfterDiameter[0].y, 2));

	area_table = height * width;

	double current_area = 0;
	current_area += abs((endPointsAfterDiameter[0].x * endPointsAfterDiameter[1].y + endPointsAfterDiameter[1].x * for_check.y + for_check.x * endPointsAfterDiameter[0].y - endPointsAfterDiameter[0].y * endPointsAfterDiameter[1].x - endPointsAfterDiameter[1].y * for_check.x - for_check.y * endPointsAfterDiameter[0].x) / 2);
	current_area += abs((endPointsAfterDiameter[1].x * endPointsAfterDiameter[2].y + endPointsAfterDiameter[2].x * for_check.y + for_check.x * endPointsAfterDiameter[1].y - endPointsAfterDiameter[1].y * endPointsAfterDiameter[2].x - endPointsAfterDiameter[2].y * for_check.x - for_check.y * endPointsAfterDiameter[1].x) / 2);
	current_area += abs((endPointsAfterDiameter[2].x * endPointsAfterDiameter[3].y + endPointsAfterDiameter[3].x * for_check.y + for_check.x * endPointsAfterDiameter[2].y - endPointsAfterDiameter[2].y * endPointsAfterDiameter[3].x - endPointsAfterDiameter[3].y * for_check.x - for_check.y * endPointsAfterDiameter[2].x) / 2);
	current_area += abs((endPointsAfterDiameter[3].x * endPointsAfterDiameter[0].y + endPointsAfterDiameter[0].x * for_check.y + for_check.x * endPointsAfterDiameter[3].y - endPointsAfterDiameter[3].y * endPointsAfterDiameter[0].x - endPointsAfterDiameter[0].y * for_check.x - for_check.y * endPointsAfterDiameter[3].x) / 2);

	if (current_area -area_table < 1e-10)
	{
		return true;
	}
	return false;
}

map<int, Point> Field::which_wall_crossing(Line dl, Point start, Point end) // Функция, която проверява стената на удар и кординаните, в които се е ударило топчето в дадената стена.
{
	double length = 2000, current_length;
	int index = 1;
	double x = 0, y = 0;
	map<int, Point> wall_and_point;

	for (auto wl : wall_lines)
	{
		x = (wl.get_B() * dl.get_C() - dl.get_B() * wl.get_C()) / (wl.get_A() * dl.get_B() - dl.get_A() * wl.get_B());
		y = (wl.get_C() * dl.get_A() - dl.get_C() * wl.get_A()) / (wl.get_A() * dl.get_B() - dl.get_A() * wl.get_B());

		Point possible_point(x, y);
	
		if (is_point_in_table(possible_point))
		{
			current_length = sqrt(pow(x - end.x, 2) + pow(y - end.y, 2));

			if (current_length < length)
			{
				Point final_collision_point(x, y);
				int required_index;
				length = current_length;
				
				if (is_equal(final_collision_point, endPointsAfterDiameter[0]))
				{
					required_index = 1; 
				}
				else if (is_equal(final_collision_point, endPointsAfterDiameter[1]))
				{
					required_index = 2;
				}
				else if (is_equal(final_collision_point, endPointsAfterDiameter[2]))
				{
					required_index = 3;
				}
				else if (is_equal(final_collision_point, endPointsAfterDiameter[3]))
				{
					required_index = 4;
				}
				else
				{
					required_index = index;
				}

				wall_and_point.clear();
				wall_and_point.insert({required_index, final_collision_point});
			}
		}
		index++;
	}
	
	return wall_and_point;
}

double Field::find_mirror_x(double x_hit, Point end_point) // Функция, която намира огледалния кординат Х.
{
	double difference_x = end_point.x - x_hit;
	double mirror_x;

	if (difference_x > 0)
	{
		mirror_x = x_hit - difference_x;
	}
	else if (difference_x < 0)
	{
		mirror_x = x_hit + abs(difference_x);
	}
	else
	{
		mirror_x = x_hit;
	}

	return mirror_x;
}

double Field::find_mirror_y(double y_hit, Point end_point) // Функция, която намира огледалния кординат Y.
{
	double difference_y = end_point.y - y_hit;
	double mirror_y;

	if (difference_y > 0)
	{
		mirror_y = y_hit - difference_y;
	}
	else if (difference_y < 0)
	{
		mirror_y = y_hit + abs(difference_y);
	}
	else
	{
		mirror_y = y_hit;
	}

	return mirror_y;
}

Point Field::mirror_point(Line wall, Line perpendicular, Point end_point) //Функция, която намира огледалните кординати на точка, спрямо права, като ги намира с помощта на горните 2 функции.
{
	double x = (wall.get_B() * perpendicular.get_C() - perpendicular.get_B() * wall.get_C()) / (perpendicular.get_B() * wall.get_A() - wall.get_B() * perpendicular.get_A());
	double y = (wall.get_C() * perpendicular.get_A() - perpendicular.get_C() * wall.get_A()) / (wall.get_A() * perpendicular.get_B() - perpendicular.get_A() * wall.get_B());

	double mirrored_x = find_mirror_x(x, end_point);
	double mirrored_y = find_mirror_y(y, end_point);
	
	return Point(mirrored_x, mirrored_y);
}

void Field::hit(Point target, double power)
{
	while(!is_power_valid(power))
	{
		cout << "This is not valid power! Write new one!" << endl;
		cin >> power; 
	}

	while(!is_point_in_table(startingPoint) || is_in_any_angle(endPointsAfterDiameter,startingPoint))
	{
		cout << "Starting point is not valid or it's on some angle! Write new point!" << endl;
		cin >> startingPoint;
	}

	Point startingPoint = initiliaze_point(ball.center);
	Point copy_starting = initiliaze_point(startingPoint); // Тази точка е в случай, когато ударим някоя стена и отблъскването отиде в ъгъл. 
	//Ако работя само със startingPoint, при повече от едно отблъскване, ще загубя началната точка, променяйки startingPoint. 
	Vector all_distance(startingPoint, target);
	all_distance.Multiply(all_distance, power);
	Point end_point = find_point(all_distance, startingPoint);

	if (is_point_in_table(end_point)) // Проверявам дали крайната точка е вътре, защото ако е, да не влизам по-долу в уайла.
	{
		if(is_in_any_angle(endPointsAfterDiameter, end_point)) // Ако удря и в някой ъгъл, връщаме кординаните в началото.
		{
			ball.center = startingPoint;
			return;
		}
		ball.center = end_point;
		return;
	}

	make_wall_lines(); // Правя правите между всеки 2 точки.
	map<int, Point> wall_and_position;
	Point finded_mirror_point;
	bool is_already_ball_in_table = false;

	while (1)
	{
		Line direction_line(startingPoint, end_point); 
		wall_and_position = which_wall_crossing(direction_line, startingPoint, end_point);
	
		for (auto i : wall_and_position)
		{
			if (i.first == 1)
			{
				if (is_equal(i.second, endPointsAfterDiameter[0]))
				{
					Point end(copy_starting.x, copy_starting.y);
					ball.center = end;
					return;
				}

				else
				{
					Line perpendicular = wall_lines[0].perpendicular(end_point);
					finded_mirror_point = mirror_point(wall_lines[0], perpendicular, end_point);
				}
			}

			else if (i.first == 2)
			{
				if (is_equal(i.second, endPointsAfterDiameter[1]))
				{
					Point end(copy_starting.x, copy_starting.y);
					ball.center = end;
					return;
				}
				else
				{
					Line perpendicular = wall_lines[1].perpendicular(end_point);
					finded_mirror_point = mirror_point(wall_lines[1], perpendicular, end_point);
				}
			}

			else if (i.first == 3)
			{
				if (is_equal(i.second, endPointsAfterDiameter[2]))
				{
					Point end(copy_starting.x, copy_starting.y);
					ball.center = end;
					return;
				}
				else
				{
					Line perpendicular = wall_lines[2].perpendicular(end_point);
					finded_mirror_point = mirror_point(wall_lines[2], perpendicular, end_point);
				}
			}
			
			else
			{
				if (is_equal(i.second, endPointsAfterDiameter[3]))
				{
					Point end(copy_starting.x, copy_starting.y);
					ball.center = end;
					return;
				}
				else
				{
					Line perpendicular = wall_lines[3].perpendicular(end_point);
					finded_mirror_point = mirror_point(wall_lines[3], perpendicular, end_point);
				}
			}

			if (is_point_in_table(finded_mirror_point))
			{
				is_already_ball_in_table = true;
				break;
			}

			else
			{
				startingPoint = initiliaze_point(i.second);
				end_point = initiliaze_point(finded_mirror_point);
			}
		}

		if (is_already_ball_in_table)
		{
			break;
		}
	}

	ball.center = finded_mirror_point;
}

ostream &operator<<(ostream &os, const Field &f)
{
	os << "Field points:" << endl;
	for (int i = 0; i < 4; i++)
		os << "  " << f.endPoints[i] << endl;

	os << f.ball;
	return os;
}

void simpleCase(Field &f)
{
	Point origin;
	double width, height;
	Ball ball;
	cout << "Point of origin of field: ";
	cin >> origin;
	cout << "Width and height of field: ";
	cin >> width >> height;
	cin >> ball;
	f = Field(origin, width, height, ball);
}

void complexCase(Field &f)
{
	Point endPoints[4];
	Ball ball;
	cout << "Field points: " << endl;
	for (int i = 0; i < 4; ++i)
	{
		cout << "  " << i + 1 << ") ";
		cin >> endPoints[i];
	}
	cin >> ball;
	f = Field(endPoints, ball);
}

void ballCase(Field &f)
{
	Ball ball;
	cin >> ball;
	f = Field(f.endPoints, ball);
}