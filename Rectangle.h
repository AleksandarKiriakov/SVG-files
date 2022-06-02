#pragma once
#include "Shape.h"
#include "Mystring.h"
class Rectangle : public Shape
{
	double width;
	double height;
public:
	Rectangle(double x1, double y1, double width, double height, MyString Fill);
	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;
	void print() const override;
	void increasePoints(double vertical, double horizontal) override;
	double getHeight() const override;
	double getWidth() const override;
};