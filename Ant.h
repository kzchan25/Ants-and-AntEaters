#ifndef Ant_h
#define Ant_h

#include "Controller.h"
#include "PointHasher.h"

class Ant : public Organism {
private:
    
public:
    
    Ant() {
        charID = "a";
        reproduceThreshhold = 3;
    }
    
    Ant(Point location) {
        charID = "a";
        reproduceThreshhold = 3;
        this -> location.x = location.x;
        this -> location.y = location.y;
    }
    
    Ant(Point* location) {
        charID = "a";
        reproduceThreshhold = 3;
        this -> location = location;
    }
};

#endif /* Ant_h */


