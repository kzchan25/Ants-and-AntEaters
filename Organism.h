#ifndef Organism_h
#define Organism_h

#include <unordered_map>
#include <vector>
#include <time.h>
#include "PointHasher.h"
#include "Controller.h"

class Organism {
protected:
    Point location;
    int lifeSpan = 1;
    bool dead = false;
    bool moved;
    string charID;
    int reproduceThreshhold;
public:
    Organism() {
        charID = "O";
        location = Point(0, 0);
    }
    Organism(Point* location) {
        charID = "O";
        this -> location.x = location -> x;
        this -> location.y = location -> y;
    }
    
    void setMoved(bool moved) {
        this -> moved = moved;
    }
    
    bool getMoved() {
        return moved;
    }
    
    int getX() const {
        return location.x;
    }
    int getY() const {
        return location.y;
    }
    Point getLocation() const {
        return location;
    }
    
    Point* getPoint() {
        return &location;
    }
    
    int getLifeSpan() const {
        return lifeSpan;
    }
    
    bool isDead() {
        return dead;
    }
    
    void setDead(bool dead) {
        this -> dead = dead;
    }
    
    static bool spaceIsClear(Point point, unordered_map<Point, Organism*, PointHasher> organisms) {
        return !(organisms.find(point) != organisms.end());
    }
    
    static bool inBounds(Point point, int width, int height) {
        return !(point.x >= width || point.x < 0 || point.y >= height || point.y < 0);
    }
    
    static bool adjacentSpaceIsClear(Point point, unordered_map<Point, Organism*, PointHasher> organisms) {
        return spaceIsClear(Point(point.x, point.y - 1), organisms) ||
               spaceIsClear(Point(point.x - 1, point.y), organisms) ||
               spaceIsClear(Point(point.x, point.y + 1), organisms) ||
               spaceIsClear(Point(point.x + 1, point.y), organisms);
    }

    static Point adjacentSpace(Point point, unordered_map<Point, Organism*, PointHasher> organisms, int width, int height) {
        vector<Point> spaces;
        for (int i = -1; i < 2; i += 2) {
            if (spaceIsClear(Point(point.x, point.y + i), organisms) &&
                inBounds(Point(point.x, point.y + i), width, height)) {
                spaces.push_back(Point(point.x, point.y + i));
            }
            if (spaceIsClear(Point(point.x + i, point.y), organisms) &&
                inBounds(Point(point.x + i, point.y), width, height)) {
                spaces.push_back(Point(point.x + i, point.y));
            }
        }
        if (spaces.empty()) {
            return point;
        }
        
        return spaces[(int)(((double)(rand())/(RAND_MAX)) * spaces.size())];
    }
    
    bool reproduceFlag() {
        if (lifeSpan >= reproduceThreshhold) {
            lifeSpan = 0;
            return true;
        }
        return false;
    }
    
    virtual Point move(unordered_map<Point, Organism*, PointHasher> orgs, int width, int height) {
        lifeSpan++;
        location = adjacentSpace(location, orgs, width, height);
        return location;
    }
    
    string getChar() const{
        return charID;
    }
    friend ostream & operator << (ostream &out, const Organism &organism);
};

ostream & operator << (ostream &out, const Organism &organism) {
    out << "[" << organism.getLocation().x << ", " << organism.getLocation().y <<
    " : " << organism.getLifeSpan() << " : ID: " << organism.getChar() << "]";
    return out;
}

#endif /* Organism_h */
