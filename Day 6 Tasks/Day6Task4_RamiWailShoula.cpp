//Day6Task4_RamiWailShoula.cpp
//Implementing GeometricShape Base Class as Parent Class for Circle , 
//Triangle and Rectangle and Square Classes to calculate the Area of geometric shapes;

#include<iostream>
using namespace std;

//GeometricShape Base Class as Parent Class
class GeometricShape
{
public:
	double height, base, radius;
	GeometricShape()
	{
		height = 0;
		base = 0;
		radius = 0;
	}
	void get_data()
	{
		cout << "\nKindly enter height: "; cin >> height;
		cout << "\nKindly enter base: ";	cin >> base;
	}
	virtual void display_area()
	{
	}
};

class Circle : public GeometricShape
{
public:
	void get_data()
	{
		cout << "1)Circle:\nKindly enter radius of circle: ";
		cin >> radius;
	}
	void display_area()
	{
		cout << "\nArea of Circle = (pi*r^2) = 3.14 * r * r = " << 3.14 * radius * radius;
	}
};


class Triangle : public GeometricShape
{
public:

	void display_area()
	{
		cout << "\nArea of Triangle = (1/2 * base * height) = " << (height * base) / 2;
	}
};

class Rectangle : public GeometricShape
{
public:

	void display_area()
	{
		cout << "\nArea of Rectangle = (height * base) = " << height * base;
	}
};

class Square : public GeometricShape
{
public:
	void get_data()
	{
		cout << "\nKindly Enter base of the square: ";
		cin >> base;
	}
	void display_area()
	{
		cout << "\nArea of Square = (base * base) = " << base * base;
	}
};

void main()
{
	GeometricShape* s;
	Circle c;
	c.get_data();
	s = &c;
	s->display_area();
	cout << "\n\n2)Triangle:";
	Triangle t;
	t.get_data();
	s = &t;
	s->display_area();
	cout << "\n\n3)Rectangle:";
	Rectangle r;
	r.get_data();
	s = &r;
	s->display_area();
	cout << "\n\n4)Square:\n";
	Square q;
	q.get_data();
	s = &q;
	s->display_area();
	cout << endl << endl;
}