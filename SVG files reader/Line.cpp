#include "Line.h"

Line::Line(double x1, double y1, double width, double height) :Shape(2,"Line","No")
{
	if (x1 < 0)
	{
		x1 *= (-1);
	}
	if (y1 < 0)
	{
		y1 *= (-1);
	}
	setPoint(0, x1, y1);
	setPoint(1, (width), (height));
}

double Line::getArea() const
{
	std::cout << "Line has no area!";
	return -1;
}

Shape* Line::clone() const
{
	return new Line(*this);
}

void Line::print() const
{
	Shape::point p0 = getPointAtIndex(0);
	Shape::point p1 = getPointAtIndex(1);

	std::cout << "Line " << p0.x << " " << p0.y << " " << p1.x << " " << p1.y << " ";

}

void Line::increasePoints(double vertical, double horizontal)
{
	double x1 = getX(0);
	x1 += horizontal;
	double y1 = getY(0);
	y1 += vertical;
	setPoint(0, x1, y1);
	double x2 = getX(1);
	x2 += horizontal;
	double y2 = getY(1);
	y2 += vertical;
	setPoint(1, x2, y2);
}

double Line::getWidth() const
{
	return 0;
}

double Line::getHeight() const
{
	return 0;
}

double Line::getPer() const
{
	std::cout << "Line has no peremiter!";
	return -1;
}

bool Line::isPointIn(double x, double y) const
{
	Shape::point p(x, y);
	Shape::point p0 = getPointAtIndex(0);
	Shape::point p1 = getPointAtIndex(1);
	double AB = sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
	double AP = sqrt((p.x - p0.x) * (p.x - p0.x) + (p.y - p0.y) * (p.y - p0.y));
	double PB = sqrt((p1.x - p.x) * (p1.x - p.x) + (p1.y - p.y) * (p1.y - p.y) );
	return AB == (AP + PB);
}