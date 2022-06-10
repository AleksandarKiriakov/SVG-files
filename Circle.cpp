#include "Circle.h"

const double PI = 3.1415;
Circle::Circle(double x, double y, double radius, MyString Fill) : Shape(1,"Circle",Fill), radius(radius)
{
	if (x < 0)
	{
		x *= (-1);
	}
	if (y < 0)
	{
		y *= (-1);
	}
	setPoint(0, x, y);
}

double Circle::getArea() const
{
	return PI * radius * radius;
}
double Circle::getPer() const
{
	return 2 * PI * radius;
}
bool Circle::isPointIn(double x, double y) const
{
	Shape::point p(x, y);
	return p.getDist(getPointAtIndex(0)) <= radius;
}
Shape* Circle::clone() const
{
	Shape* copy = new Circle(*this);
	return copy;
}

void Circle::print() const
{
	Shape::point p0 = getPointAtIndex(0);
	std::cout << "Circle " << p0.x << " " << p0.y << " " <<radius<<" "<<getFill()<< std::endl;
}

void Circle::increasePoints(double vertical, double horizontal)
{
	double x1 = getX(0);
	x1 += horizontal;
	double y1 = getY(0);
	y1 += vertical;
	setPoint(0, x1, y1);
}

double Circle::getWidth() const
{
	return radius;
}

double Circle::getHeight() const
{
	return radius;
}

