//Day6Task3_RamiWailShoula.cpp
//Class Picture , Class Point, Class Circle, Class Rectangle and Class Line

//includes
#include<iostream>
#include<algorithm>
#include<string>
#include <math.h>
#include"ITI.h"

#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

using namespace std;
using std::string;


class Point {
public:
    Point(int x, int y);
    int getX() const;
    int getY() const;
    void setX(int nx);
    void setY(int ny);
    void move(int dx, int dy);
    double distanceTo(const Point& p) const;
    /* ... */
private:
    int x, y;
};

Point::Point(int x, int y)
{
    Point::x = x;
    this->y = y;
}

double
Point::distanceTo(const Point& p) const
{
    double dx = x - p.getX();
    double dy = y - p.getY();
    return sqrt(dx * dx + dy * dy);
}

int
Point::getX() const
{
    return x;
}

int
Point::getY() const
{
    return y;
}

void
Point::setY(int y)
{
    this->y = y;
}

void
Point::setX(int x)
{
    this->x = x;
}

void
Point::move(int dx, int dy)
{
    x += dx;
    y += dy;
}

class Rect {
public:
    Rect(int x, int y, int width, int height);
    void move(int dx, int dy);
    bool pointInside(const Point& p) const;

    // bad: exposes implementation details...
    const Point& getUpperLeft() const {
        return upperleft;
    }

    /* ... */
private:
    Point upperleft;
    int width, height;
};

Rect::Rect(int x, int y, int width, int height)
    : upperleft(x, y)
{
    this->width = width;
    this->height = height;
}

void
Rect::move(int dx, int dy)
{
    upperleft.move(dx, dy);
}

bool
Rect::pointInside(const Point& p) const
{
    if (upperleft.getX() <= p.getX()
        && p.getX() <= upperleft.getX() + width
        && upperleft.getY() <= p.getY()
        && p.getY() <= upperleft.getY() + height)
        return true;
    return false;
}

class Display {
public:
    Display();
    ~Display();
    void drawLine(const Point& from,
        const Point& to);
    void update();
};

class Shape {
public:
    Shape();
    virtual void move(int dx, int dy) = 0;
    virtual void draw(Display& d) = 0;
    virtual ~Shape();
};

class Circle : public Shape {
public:
    Circle(const Point& center, int radius);
    void move(int dx, int dy);
    void draw(Display& d);
private:
    Point center;
    int radius;
};

class Rectangle : public Shape {
public:
    Rectangle(const Point& ul, const Point& lr);
    void move(int dx, int dy);
    void draw(Display& d);
protected:
    Point upperLeft;
    Point lowerRight;
};

class GridRectangle : public Rectangle {
public:
    GridRectangle(const Point& ul, const Point& lr, int sep);
    void draw(Display& d);
protected:
    int gridSep;
};

class Picture : public Shape {
public:
    Picture(int nElem);
    bool setElement(int index, Shape* s);
    void move(int dx, int dy);
    void draw(Display& d);
    ~Picture();
private:
    int nElements;
    Shape** elements;
};

// Shape class

Shape::Shape()
{
}

Shape::~Shape()
{
}


// Circle class

Circle::Circle(const Point& center, int radius)
    : center(center), radius(radius)
{
}

void
Circle::move(int dx, int dy)
{
    center.move(dx, dy);
}

void
Circle::draw(Display& d)
{
    // ...
}

// Rectangle class

Rectangle::Rectangle(const Point& ul,
    const Point& lr)
    : upperLeft(ul), lowerRight(lr)
{
}

void
Rectangle::move(int dx, int dy)
{
    upperLeft.move(dx, dy);
    lowerRight.move(dx, dy);
}

void
Rectangle::draw(Display& d)
{
    Point ur(lowerRight.getX(),
        upperLeft.getY());
    Point ll(upperLeft.getX(),
        lowerRight.getY());
    d.drawLine(upperLeft, ur);
    d.drawLine(ur, lowerRight);
    d.drawLine(lowerRight, ll);
    d.drawLine(ll, upperLeft);
}

// Grid rectangle class

GridRectangle::GridRectangle(const Point& ul,
    const Point& lr,
    int sep)
    : Rectangle(ul, lr), gridSep(sep)
{
}

void
GridRectangle::draw(Display& d)
{
    // Draw outline
    Rectangle::draw(d);

    // Draw vertical grid lines
    for (int x = upperLeft.getX() + gridSep / 2
        ; x < lowerRight.getX(); x += gridSep)
    {
        Point p1(x, upperLeft.getY());
        Point p2(x, lowerRight.getY());
        d.drawLine(p1, p2);
    }
    // Draw horizontal grid lines
    for (int y = upperLeft.getY() + gridSep / 2
        ; y < lowerRight.getY(); y += gridSep)
    {
        Point p1(upperLeft.getX(), y);
        Point p2(lowerRight.getX(), y);
        d.drawLine(p1, p2);
    }
}

// Picture class

Picture::Picture(int nElem)
    : nElements(nElem)
{
    elements = new Shape * [nElements];
    int i;

    for (i = 0; i < nElements; i++)
        elements[i] = 0;
}

void
Picture::draw(Display& d)
{
    int i;

    for (i = 0; i < nElements; i++)
        if (elements[i])
            elements[i]->draw(d);
}

void
Picture::move(int dx, int dy)
{
    int i;

    for (i = 0; i < nElements; i++)
        if (elements[i])
            elements[i]->move(dx, dy);
}

bool
Picture::setElement(int index, Shape* s)
{
    if (index < 0 || index >= nElements)
        return false;
    elements[index] = s;
    return true;
}

Picture::~Picture()
{
    delete[] elements;
}

//driving shit
int main()
{
    Display display;
    Rectangle r(Point(2, 2), Point(6, 4));
    GridRectangle gr(Point(10, 4), Point(16, 9),
        3);
    Circle c(Point(0, 4), 8);

    Picture subpic(2);
    subpic.setElement(0,
        new Circle(Point(10, 2), 3));
    subpic.setElement(1,
        new Rectangle(Point(7, 5), Point(13, -1)));

    Picture pic(4);

    pic.setElement(0, &r);
    pic.setElement(1, &c);
    pic.setElement(2, &subpic);
    pic.setElement(3, &gr);

    pic.draw(display);

    display.update();

    return 0;
}