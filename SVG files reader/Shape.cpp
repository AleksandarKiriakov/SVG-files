#include "Shape.h"

Shape::Shape(size_t pointsCount, MyString shape,MyString fill) : pointsCount(pointsCount), shape(shape),fill(fill)
{
	points = new point[pointsCount]; // [0,0], [0,0]....
}

void Shape::copyFrom(const Shape& other)
{
	points = new point[other.pointsCount];

	for (size_t i = 0; i < other.pointsCount; i++)
		points[i] = other.points[i];

	pointsCount = other.pointsCount;
}
void Shape::free()
{
	delete[] points;
}

Shape::Shape(const Shape& other)
{
	copyFrom(other);
}
Shape& Shape::operator= (const Shape& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Shape::~Shape()
{
	free();
}

const Shape::point& Shape::getPointAtIndex(size_t index) const
{
	if (index >= pointsCount)
		throw std::exception("Invalid point index!");

	return  points[index];
}

void Shape::setPoint(size_t pointIndex, double x, double y)
{
	if (pointIndex >= pointsCount)
		throw std::exception("Invalid point index!");

	points[pointIndex] = point(x, y);
}

double Shape::getX(int i)
{
	return points[i].x;
}

double Shape::getY(int i)
{
	return points[i].y;
}

const MyString& Shape::getShape() const
{
	return shape;
}

const MyString& Shape::getFill() const
{
	return fill;
}

void Shape::setShape(const MyString& s)
{
	shape += s;
}