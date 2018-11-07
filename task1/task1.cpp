#include <iostream>
#include <math.h>
using namespace std;
class Point
{
  public:
    Point(float _x, float _y);
    ~Point();
    float GetX();
    float GetY();
    float Distance();
    float Distance(Point p);
    void Display();
    float x;
    float y;
};

class Line
{
  public:
    Line(float x1, float y1, float x2, float y2);
    Line(Point _x, Point _y);
    ~Line();
    float Length();
    void Display();
    float Distance(Point p);
    Point x, y;
};

int main()
{
    Point A(1, 2);
    Point B(5, 7);
    cout << "A";
    A.Display();
    cout << "----";
    cout << "B";
    B.Display();
    cout << ",";
    cout << "Distance=";
    cout << A.Distance(B);
    cout << endl;
    Line AB(A, B);
    cout << "AB:";
    AB.x.Display();
    cout << "--";
    AB.y.Display();
    cout << ",Length=" << AB.Length() << ",MidPoint:";
    AB.Display();
    cout << endl;
    return 0;
}

Point::Point(float _x, float _y)
{
    x = _x;
    y = _y;
}

Point::~Point()
{
}

float Point::GetX()
{
    return x;
}

float Point::GetY()
{
    return y;
}

float Point::Distance()
{
    return sqrt(x * x + y * y);
}

float Point::Distance(Point p)
{
    return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
}

void Point::Display()
{
    cout << "(" << x << "," << y << ")";
}

Line::Line(float x1, float y1, float x2, float y2) : x(x1, y1), y(x2, y2)
{
}

Line::Line(Point _x, Point _y) : x(_x.GetX(), _x.GetY()), y(_y.GetX(), _y.GetY())
{
}

Line::~Line()
{
}

float Line::Length()
{
    return y.Distance(x);
}

float Line::Distance(Point p)
{
    float s = (1 / 2) * (x.GetX() * y.GetY() + y.GetX() * p.GetY() + p.GetX() * x.GetY() - x.GetX() * p.GetY() - y.GetX() * x.GetY() - p.GetX() * y.GetY());
    float d = this->Length();
    return s / d * 2;
}

void Line::Display()
{
    Point p((x.GetX() + y.GetX()) / 2, (x.GetY() + y.GetY()) / 2);
    p.Display();
}