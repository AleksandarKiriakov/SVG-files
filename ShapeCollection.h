#pragma once
#include "Shape.h"
#include "Mystring.h"
class ShapeCollection
{
	Shape** shapes;
	int shapesCount;
	size_t capacity;

	void free();
	void copyFrom(const ShapeCollection& other);
	void resize();

	void addShape(Shape* shape,MyString& shapeName);
	void parseBuffer(char* buffer);
public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection& operator=(const ShapeCollection& other);
	~ShapeCollection();


	void addRectangle(double x1, double y1, double width, double height, MyString Fill);
	void addCircle(double x1, double y1, double r, MyString Fill);

	void addLine(double x1, double y1, double width, double height);

	double getPerOfFigureByIndex(int ind) const;
	double getAreaOfFigureByIndex(int ind) const;
	void print();
	void PointIn(double x, double y);
	void erase(double place);
	void openFile();
	void withInRectange(double x, double y, double width, double height);
	void withInCircle(double x, double y, double radius);
	void translate(double vertical, double horisontal, int numberOFShape);
	void saveToFile();
	void getAreas() const;
	void getPeremetes() const;
};