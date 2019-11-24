#ifndef Point_h
#define Point_h

#include <cmath>

using namespace std;
class Point {
    public:
    int x;
    int y;
    
    Point() {
        x = 0;
        y = 0;
    }
    
    Point(Point* other) {
        this -> x = other -> x;
        this -> y = other -> y;
    }
    
    Point(const Point &other) {
        this -> x = other.x;
        this -> y = other.y;
    }
    
    Point(int x, int y) {
        this -> x = x;
        this -> y = y;
    }
    
    float dist(Point* other) {
        return sqrt(pow(this -> x - other -> x, 2) + pow(this -> y - other -> y, 2));
    }
    
    bool operator==(const Point& point) const {
        return x == point.x && y == point.y;
    }
    
    friend ostream & operator << (ostream &out, const Point &point);
};

ostream & operator << (ostream &out, const Point &point) {
    out << "[" << point.x << ", " << point.y << "]";
    return out;
}

#endif /* Point_h */
