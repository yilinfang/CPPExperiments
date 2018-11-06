#include <iostream>
#include <math.h>
using namespace std;
class Point{
    public:
    Point(float _x, float _y);
    ~Point();
    float GetX();
    float GetY();
    float Distance();
    float Distance(Point p);
    void Display();
    private:
    float x;
    float y;
};
