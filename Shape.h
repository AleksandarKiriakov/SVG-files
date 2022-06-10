#pragma once
#include <iostream>
#include "Mystring.h"

class Shape  
{
protected:
	struct point
	{
		point() :x(0), y(0) {}
		point(double x, double y) :x(x), y(y) {}
		double x;
		double y;
		double getDist(const point& other) const
		{
			double dx = x - other.x;
			double dy = y - other.y;

			return sqrt(dx * dx + dy * dy);
		}

	};
	const point& getPointAtIndex(size_t index) const;
private:
	point* points;
	size_t pointsCount;
	MyString shape;
	MyString fill;
	void copyFrom(const Shape& other);
	void free();


public:
	Shape(size_t pointsCount, MyString shape,MyString fill);

	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	virtual ~Shape();

	void setPoint(size_t pointIndex, double x, double y);

	virtual void print() const = 0;
	virtual double getArea() const = 0;
	virtual double getPer()  const = 0;
	virtual bool isPointIn(double x, double y) const = 0;
	virtual Shape* clone() const = 0;
	virtual void increasePoints(double vertical, double horizontal) =0;
	double getX(int i);
	double getY(int i);
	virtual double getHeight() const = 0;
	virtual double getWidth() const = 0;
	const MyString& getShape() const ;
	const MyString& getFill()const;
	void setShape(const MyString& s);
};