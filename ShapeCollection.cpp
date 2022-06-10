#include "ShapeCollection.h"
#include <stdexcept>     
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include <fstream>
const int buffSize = 1024;
void ShapeCollection::free()
{
	for (int i = 0; i < shapesCount; i++)
		delete shapes[i]; 
	delete[] shapes;
}
void ShapeCollection::copyFrom(const ShapeCollection& other)
{
	shapes = new Shape * [other.shapesCount];
	shapesCount = other.shapesCount;
	capacity = other.capacity;

	for (int i = 0; i < shapesCount; i++)
	{
		shapes[i] = other.shapes[i]->clone();
	}
}

void ShapeCollection::resize()
{
	Shape** newCollection = new Shape * [capacity *= 2];
	for (int i = 0; i < shapesCount; i++)
		newCollection[i] = shapes[i]; 
	delete[] shapes;
	shapes = newCollection;
}

ShapeCollection::ShapeCollection()
{
	capacity = 8;
	shapesCount = 0;
	shapes = new Shape * [capacity];
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copyFrom(other);
}
ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
ShapeCollection::~ShapeCollection()
{
	free();
}

void ShapeCollection::addShape(Shape* shape,MyString& shapeNmae)
{
	if (shapesCount == capacity)
		resize();
	int i = 0;
	for (; i <= shapesCount; i++)
	{
		if (shapes[i]==nullptr)
		{
			break;
		}
	}
	if (i < shapesCount)
	{
		shapes[i] = shape;
		shapes[i]->setShape(shapeNmae);
	}
	else
	{
		shapes[shapesCount++] = shape;
		
	}
	
}



void ShapeCollection::addRectangle(double x1, double y1, double width, double height, MyString Fill)
{
	MyString s = "Rectangle";
	Rectangle* rect = new Rectangle(x1, y1, width, height,Fill);
	addShape(rect,s);
}
void ShapeCollection::addCircle(double x1, double y1, double r,MyString Fill)
{
	MyString s = "Circle";
	Circle* circlce = new Circle(x1, y1, r,Fill);
	addShape(circlce,s);

}
void ShapeCollection::addLine(double x1, double y1, double width, double height)
{
	MyString s = "Line";
	Line* ln = new Line(x1, y1, width, height);
	addShape(ln, s);
}

double ShapeCollection::getPerOfFigureByIndex(int ind) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	if (shapes[ind]==nullptr)
	{
		return 0;
	}
	return shapes[ind]->getPer();
}
double ShapeCollection::getAreaOfFigureByIndex(int ind) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	if (shapes[ind] == nullptr)
	{
		return 0;
	}
	return shapes[ind]->getArea();
}

void ShapeCollection::print()
{
	int counter = 0;
	for (int i = 0; i < shapesCount; i++)
	{
		if (shapes[i]==nullptr)
		{
			continue;
		}
		std::cout << counter++ << ". ";
		shapes[i]->print();
	}
}

void ShapeCollection::PointIn(double x, double y)
{
	bool inFigure = true;
	for (int i = 0; i < shapesCount; i++)
	{
		if (!(shapes[i]==nullptr))
		{
			if (shapes[i]->isPointIn(x, y))
			{
				inFigure = false;
				shapes[i]->print();
			}
		}
	}
	if (inFigure)
	{
		std::cout << "This point in not in any figures";
	}
}

void ShapeCollection::erase(double place)
{
	if (place> shapesCount)
	{
		std::cout << "There is no figure number "<< place<<"!";
		return;
	}
	delete shapes[(int)place];
	shapes[(int)place] = nullptr;
}

void ShapeCollection::openFile()
{
	std::ifstream file("figures.svg");
	if (!file.is_open())
		throw "Error opening file";
	char buffer[buffSize];
	while (!file.eof())
	{
		file.getline(buffer, buffSize);
		if (strcmp(buffer,"<svg>")==0)
		{
			while (true)
			{
				file.getline(buffer, buffSize);
				if (strcmp(buffer, "</svg>") == 0)
				{
					break;
				}
				parseBuffer(buffer);
			}
		}
	}
}
void ShapeCollection::parseBuffer(char* buffer)
{
	char parser[buffSize]="\0";
	int count1 = 0;
		while (!(strcmp(buffer, "/>") == 0))
		{
			if (count1 <1)
			{
				buffer++;
				buffer++;
				count1++;
			}
			
			for (size_t i = 0; buffer[0] != ' '; i++)
			{
				parser[i] = *buffer;
				buffer++;
				parser[i + 1] = '\0';
			}
			if (strcmp(parser, "rect") == 0)
			{
				while (!(strcmp(buffer, "/>") == 0))
				{
					int y = 0;
					int height = 0;
					int x = 0;
					int width = 0;
					int count = 0;
					for (size_t i = 0; *buffer != 'f'; i++, buffer++)
					{
						if (*buffer < '9' && *buffer > '0')
						{
							while (*buffer <= '9' && *buffer >= '0')
							{
								(height *= 10) += *buffer - '0';
								buffer++;
							}
							if (count == 0)
							{
								x = height;
								height = 0;
								count++;
							}
							else if (count == 1)
							{
								y = height;
								height = 0;
								count++;
							}
							else if (count == 2)
							{
								width = height;
								height = 0;
								count++;
							}
						}
					}
					while (*buffer != '=')
					{
						buffer++;
					}
					buffer++;
					buffer++;
					char fill[200];
					int i = 0;
					for (; *buffer != '\"';i++)
					{
						fill[i] = *buffer;
						buffer++;
					}
					fill[i] = '\0';
					addRectangle(x, y, width, height, fill);
					buffer++;
					buffer++;
				}
			}
			else if (strcmp(parser, "circle") == 0)
			{
				while (!(strcmp(buffer, "/>") == 0))
				{
					int y = 0;
					int r = 0;
					int x = 0;
					int count = 0;
					for (size_t i = 0; (*buffer != 'f'); i++, buffer++)
					{
						if (*buffer < '9' && *buffer > '0')
						{
							while (*buffer <= '9' && *buffer >= '0')
							{
								(r *= 10) += *buffer - '0';
								buffer++;
							}
							if (count == 0)
							{
								x = r;
								r = 0;
								count++;
							}
							else if (count == 1)
							{
								y = r;
								r = 0;
								count++;
							}
						}
					}
					while (*buffer != '=')
					{
						buffer++;
					}
					buffer++;
					buffer++;
					char fill[200];
					size_t i = 0;
					for (; *buffer != '\"'; i++)
					{
						fill[i] = *buffer;
						buffer++;
					}
					fill[i] = '\0';
					addCircle(x, y, r, fill);
					buffer++;
					buffer++;
				}
			}
			else if (strcmp(parser, "line") == 0)
			{
				while (!(strcmp(buffer, "/>") == 0))
				{
					int y = 0;
					int height = 0;
					int x = 0;
					int width = 0;
					int count = 0;
					for (size_t i = 0; *buffer != '/'; i++, buffer++)
					{
						if (*buffer <= '9' && *buffer >= '0')
						{
							while (*buffer <= '9' && *buffer >= '0')
							{
								(height *= 10) += *buffer - '0';
								buffer++;
							}
							if (count == 0)
							{
								x = height;
								height = 0;
								count++;
							}
							else if (count == 1)
							{
								y = height;
								height = 0;
								count++;
							}
							else if (count == 2)
							{
								width = height;
								height = 0;
								count++;
							}
						}
					}
					addLine(x, y, width, height);
				}
			}
		}
	
}
void ShapeCollection::withInRectange(double x, double y, double width, double height)
{
	for (int i = 0; i < shapesCount; i++)
	{
		double otherX=shapes[i]->getX(0);
		double otherY = shapes[i]->getY(0);
		if (x <= otherX && y <= otherY)
		{
			if (x + width >= otherX + shapes[i]->getWidth() && y + height >= otherY + shapes[i]->getHeight())
			{
				shapes[i]->print();
			}
		}		
	}
	std::cout << std::endl;
}
double max(double x, double y)
{
	return x > y ? x : y;
}
double min(double x, double y)
{
	return x > y ? y : x;
}
void ShapeCollection::withInCircle(double x, double y, double radius)
{
	for (int i = 0; i < shapesCount; i++)
	{
		double otherX = shapes[i]->getX(0);
		double otherY = shapes[i]->getY(0);
		if (shapes[i]->getShape() == "Rectangle")
		{
			double otherX1 = shapes[i]->getX(3);
			double otherY2 = shapes[i]->getX(3);
			double Xn = max(otherX, min(x, otherX1));
			double Yn = max(otherY, min(y, otherY2));
			double Dx = Xn - x;
			double Dy = Yn - y;
			if ((Dx * Dx + Dy * Dy) <= radius * radius)
			{
				shapes[i]->print();
			}
		}
		else if(shapes[i]->getShape() == "Circle")
		{
			double otherRadius = shapes[i]->getHeight();
			if (radius >= otherRadius && otherX + otherRadius <= x + radius && otherX >= x && otherY >= y)
			{
				shapes[i]->print();
			}
		}
		else if (shapes[i]->getShape() == "Line")
		{
			double otherX1 = shapes[i]->getX(1);
			double otherY2 = shapes[i]->getX(1);
			if (x <= otherX && y <= otherY && x + radius >= otherX1 && y + radius >= otherY2)
			{
				shapes[i]->print();
			}
		}
	}
	std::cout << std::endl;
}
void ShapeCollection::translate(double vertical, double horisontal, int numberOFShape)
{
	if (numberOFShape > shapesCount)
	{
		return;
	}
	else if (numberOFShape < 0)
	{
		for (int i = 0; i < shapesCount; i++)
		{
			if (shapes[i]==nullptr)
			{
				continue;
			}
			shapes[i]->increasePoints(vertical, horisontal);
		}
	}
	else
	{
		shapes[numberOFShape]->increasePoints(vertical, horisontal);
	}

}
void ShapeCollection::saveToFile()
{
	using namespace std;
	ofstream file("figures.svg");
	if (!file.is_open())
	{
		throw "Problem writing to file";
	}
	file << "< ? xml version = \"1.0\" standalone = \"no\" ? >" <<endl;
	file << "< !DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"" << endl;
	file <<"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd \"" << endl;
	file << "<svg>"<<endl;
	for (int i = 0; i < shapesCount; i++)
	{
		if (shapes[i] != nullptr)
		{
			MyString shapeName;
			shapeName = shapes[i]->getShape();
			if (shapeName == "Rectangle")
			{
				file << " <rect x=\"" << shapes[i]->getX(0) << "\" y=\""
					<< shapes[i]->getY(0) << "\" width=\"" << shapes[i]->getWidth()
					<< " height = \"" << shapes[i]->getHeight() << "\" fill=\"" << shapes[i]->getFill() << "\" />" << endl;
			}
			else if (shapeName == "Line")
			{
				file << " <line x=\"" << shapes[i]->getX(0) << "\" y=\""
					<< shapes[i]->getY(0) << " k=\"" << shapes[i]->getX(1) << "\" z=\""
					<< shapes[i]->getY(1) << " />" << endl;

			}
			else if (shapeName == "Circle")
			{

				file << " <circle cx=\"" << shapes[i]->getX(0) << "\" cy=\""
					<< shapes[i]->getY(0) << "\" r=\"" << shapes[i]->getWidth()
					<< "\" fill=\"" << shapes[i]->getFill() << "\" />" << endl;
			}
		}
	}
	file << "</svg>";
	try
	{
		file.close();
	}
	catch (const std::exception&)
	{
		std::cout << "Problem closing file";
	}

}

void ShapeCollection::getAreas() const
{
	for (int i = 0; i < shapesCount; i++)
	{
		if (getAreaOfFigureByIndex(i)==-1)
		{
			continue;
		}
		std::cout<<getAreaOfFigureByIndex(i) << std::endl;
	}
}

void ShapeCollection::getPeremetes() const
{
	for (int i = 0; i < shapesCount; i++)
	{
		if (getAreaOfFigureByIndex(i) == -1)
		{
			continue;
		}
		std::cout << getPerOfFigureByIndex(i)<<std::endl;
	}
}
