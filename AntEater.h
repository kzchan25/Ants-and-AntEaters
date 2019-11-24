#ifndef AntEater_h
#define AntEater_h

#include "Controller.h"
#include "PointHasher.h"

typedef pair<const Point, Organism*> Pair;

class AntEater : public Organism {
private:
    int hunger = 0;
public:
    
    AntEater() {
        reproduceThreshhold = 8;
        charID = "@";
    }
    
    AntEater(Point location) {
        charID = "@";
        reproduceThreshhold = 8;
        this -> location.x = location.x;
        this -> location.y = location.y;
    }
    
    AntEater(Point* location) {
        charID = "@";
        reproduceThreshhold = 8;
        this -> location = location;
    }
    
    Point move(unordered_map<Point, Organism *, PointHasher> orgs, int width, int height) override {
        hunger++;
        if (hunger  >= 3) {
            dead = true;
        }
        return Organism::move(orgs, width, height);
    }
    
    Point* eat(unordered_map<Point, Organism*, PointHasher> *orgs) {
        for (Pair o : *orgs) {
            if (o.second -> getChar() == "a") {
                if (location.dist(o.second->getPoint()) <= 5) {
                    hunger = 0;
                    return o.second->getPoint();
                }
            }
        }
        return nullptr;
    }
};

#endif /* AntEater_h */
