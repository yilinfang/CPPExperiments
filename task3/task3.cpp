#include <iostream>
#include <math.h>
using namespace std;

#define PI 3.1415926

class Point
{
  public:
    Point(float _x, float _y);
    ~Point();
    float GetX();
    float GetY();
    float Distance();
    virtual float Distance(Point p);
    virtual void Display();
    float x;
    float y;
};

class Line : public Point
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

class Circle : public Point
{
  public:
    Circle(Point p, float r);
    Circle(float x, float y, float r);
    ~Circle();
    Point GetXY();
    float GetR();
    float Girth();
    float Area();
    void Display();
    float r;
};

void Display(Point &p);
float Distance(Point &x, Point y);

int main()
{
    Point A(1, 2), B(5, 7);
    cout << "A";
    Display(A);
    cout << "---B";
    Display(B);
    cout << ",Distance=" << Distance(A,B) << endl;
    Line AB(A, B);
    Display(AB);
    Circle C1(A, 1), C2(B, 2);
    Display(C1);
    Display(C2);
    cout << "两个圆心之间的距离,Distance=" << Distance(C1, Point(C2.x, C2.y)) << endl;
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

Line::Line(float x1, float y1, float x2, float y2) : Point((x1 + x2) / 2, (y1 + y2) / 2), x(x1, y1), y(x2, y2)
{
}

Line::Line(Point _x, Point _y) : Point((_x.GetX() + _y.GetX()) / 2, (_x.GetY() + _y.GetY()) / 2), x(_x.GetX(), _x.GetY()), y(_y.GetX(), _y.GetY())
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
    cout << "线段:";
    x.Display();
    cout << "---";
    y.Display();
    cout << ",Length=" << Length() << ",MidPoint:";
    Point::Display();
    cout << endl; 
}

Circle::Circle(Point p, float r) : Point(p.GetX(), p.GetY()), r(r){};

Circle::Circle(float x, float y, float r) : Point(x, y), r(r){};

Circle::~Circle()
{
}

Point Circle::GetXY()
{
    Point p(x, y);
    return p;
}

float Circle::GetR()
{
    return r;
}

float Circle::Girth()
{
    return 2 * r * PI;
}

float Circle::Area()
{
    return r * r * PI;
}

void Circle::Display()
{
    cout << "圆心";
    Point::Display();
    cout << "radius=" << GetR() << ",Girth=" << Girth() << ",Area=" << Area() << endl;
}


void Display(Point &p)
{
    p.Display();
}

float Distance(Point &x, Point y)
{
    return x.Distance(y);
}