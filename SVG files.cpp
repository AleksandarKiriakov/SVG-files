#include <iostream>
#include "Mystring.h"
#include "ShapeCollection.h"
using namespace std;

int main()
{
	ShapeCollection collection;
	collection.openFile();
	while (true)
	{
		cout << "1.Print 2.Create 3.Erase 4.Translate" << endl;
		cout << "5.Within 6.Point in 7.Areas 8.Pers 0.Save" << endl;
		double choice;
		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;
		if (choice==1)
		{
			collection.print();
			cout << endl;
			cout << endl;
		}
		else if (choice==2)
		{
			cout << "What type: 1.Circle 2.Rectangle 3.Line"<<endl;
			cout << "Enter your choice: ";
			cin >> choice;
			if (choice ==1)
			{
				MyString s;
				double y,radius;
				cout << "Enter x, y and radius: ";
				cin >> choice >> y >> radius;
				cout << "Enter color: ";
				cin >> s;
				collection.addCircle(choice,y,radius,s);
			}
			else if(choice ==2)
			{
				MyString s;
				double y,width,height;
				cout << "Enter x, y, width, height: ";
				cin >> choice >> y >> width>> height;
				cout << "Enter color: ";
				cin >> s;
				collection.addRectangle(choice,y, width, height, s);
			}
			else if (choice == 3)
			{
				MyString s;
				double y, width, height;
				cout << "Enter x, y, x1, y1: ";
				cin >> choice >> y >> width >> height;
				collection.addLine(choice,y, width, height);
			}
			cout << endl;
		}
		else if (choice == 3)
		{
			cout << "Enter number of figure: ";
			cin >> choice;
			collection.erase(choice);
			cout << endl;
		}
		else if (choice == 4)
		{
			cout << "1.Single figure 2.All figures" << endl;
			cout << "Enter your choice: ";
			cin >> choice;
			cout << endl;
			int horisontal;
			if (choice==1)
			{
				int numberOFigure;
				cout << "Enter vertical,horisontal,number of figure: ";
				cin >> choice >> horisontal >> numberOFigure;
				collection.translate(choice, horisontal, numberOFigure);
				cout << endl;
			}
			else if (choice==2)
			{
				cout << "Enter vertical,horisontal: ";
				cin >> choice >> horisontal;
				collection.translate(choice, horisontal, -1);
				cout << endl;
			}
			
		}
		else if (choice == 5)
		{
			cout << "Region: 1.Cirlce 2.Rectangle"<<endl;
			cout << "Enter your choice: ";
			cin >> choice;
			cout << endl;
			if (choice==1)
			{
				double y, radius;
				cout << "Enter x,y,radius: ";
				cin >> choice >> y >> radius;
				collection.withInCircle(choice,y,radius);
			}
			else if (choice==2)
			{
				double y, width, height;
				cout << "Enter x, y, width, height: ";
				cin >> choice >> y >> width >> height;
				collection.withInRectange(choice,y,width,height);
			}
			cout << endl;
		}
		else if (choice == 6)
		{
			double y;
			cout << "Enter x,y: ";
			cin >> choice >> y;
			collection.PointIn(choice, y);
			cout << endl;
			cout << endl;
		}
		else if (choice == 7)
		{
			collection.getAreas();
			cout << endl;
		}
		else if (choice == 8)
		{
			collection.getPeremetes();
			cout << endl;
		}
		else if (choice == 0)
		{
			collection.saveToFile();
			break;
		}
	}
}