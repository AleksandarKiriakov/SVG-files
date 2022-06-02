#pragma once
#include "Shape.h"
class Line : public Shape{
public:
	Line() = default;
	Line(double x1, double y1, double width, double height);
	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;
	void print() const override;
	void increasePoints(double vertical, double horizontal) override;
	double getWidth() const override;
	double getHeight() const override;
};