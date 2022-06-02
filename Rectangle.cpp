#include "Rectangle.h"



Rectangle::Rectangle(double x1, double y1, double width, double height,MyString Fill) : Shape(4,"Rectangle",Fill)
{

	this->width = width;
	this->height = height;
	if (x1<0)
	{
		x1 *= (-1);
	}
	if (y1<0)
	{
		y1 *= (-1);
	}
	setPoint(0, x1, y1);
	setPoint(1, x1, y1 + height);
	setPoint(2, x1 + width, y1 + height);
	setPoint(3, x1 + width, y1);
}


double Rectangle::getArea() const
{
	Shape::point p0 = getPointAtIndex(0);
	Shape::point p1 = getPointAtIndex(1);
	Shape::point p3 = getPointAtIndex(3);

	return p0.getDist(p1) * p0.getDist(p3);

}
double Rectangle::getPer() const
{
	Shape::point p0 = getPointAtIndex(0);
	Shape::point p1 = getPointAtIndex(1);
	Shape::point p3 = getPointAtIndex(3);

	return 2 * (p0.getDist(p1) + p0.getDist(p3));
}

bool Rectangle::isPointIn(double x, double y) const
{
	Shape::point p(x, y);
	return p.x >= getPointAtIndex(0).x && p.y >= getPointAtIndex(1).x &&
		p.y <= getPointAtIndex(0).y && p.y >= getPointAtIndex(2).y;
}
Shape* Rectangle::clone() const
{
	Shape* copy = new Rectangle(*this);
	return copy;
}

void Rectangle::print() const
{
	Shape::point p0 = getPointAtIndex(0);
	Shape::point p1 = getPointAtIndex(2);

	std::cout << "Rectangle " << p0.x << " " << p0.y << " " << p1.x << " " << p1.y<<" "<<getFill()<< std::endl;
}

void Rectangle::increasePoints(double vertical, double horizontal)
{
	double x1 = getX(0);
	x1 += horizontal;
	double y1 = getY(0);
	y1 += vertical;
	double x2 = getX(2);
	x2 += horizontal;
	double y2 = getY(2);
	y2 += vertical;
	setPoint(0, x1, y1);
	setPoint(1, x1, y2);
	setPoint(2,x2, y2);
	setPoint(3, x2, y1);
}

double Rectangle::getWidth() const
{
	return width;
}



double Rectangle::getHeight() const
{
	return height;
}
