#ifndef World_h
#define World_h

#include "Controller.h"
#include "PointHasher.h"
#include "Ant.h"
#include "AntEater.h"

typedef pair<const Point, Organism*> Pair;

using namespace std;
class World {
private:
    unordered_map<Point, Organism*, PointHasher> organisms;
    int width, height;
public:
    World() {
        this -> width = 15;
        this -> height = 15;
    }
    
    World(int width, int height) {
        this -> width = width;
        this -> height = height;
    }
    
    unsigned long getOrgCount() {
        return organisms.size();
    }
    
    int getWidth() {
        return width;
    }
    
    int getHeight() {
        return height;
    }
    
    void move(Point& from, Point& to, Organism* organism) {
        if (inBounds(to) && spaceIsClear(to)) {
            if (organisms.find(from) != organisms.end()) {
                addOrganism(organism);
                removeObject(&from);
            }
        }
    }
    
    bool full() {
        return width * height == organisms.size();
    }
    
    bool empty() {
        return organisms.size() == 0;
    }
    
    bool spaceIsClear(Point point) {
        return !(organisms.find(point) != organisms.end());
    }
    
    Organism* getOrganismAt(Point point) {
        if (organisms.find(point) != organisms.end()) {
            return organisms.find(point) -> second;
        }
        return nullptr;
    }
    
    unordered_map<Point, Organism*, PointHasher>* getOrganisms() {
        return &organisms;
    }
    
    unordered_map<Point, Organism*, PointHasher>& getAroundPoint(Point point, int dist) {
        static unordered_map<Point, Organism*, PointHasher> ret;
        ret.clear();
        for (int x = point.x - dist; x < point.x + dist; x++) {
            for (int y = point.y - dist; y < point.y + dist; y++) {
                if (organisms.find(Point(x, y)) != organisms.end() && !(Point(x, y) == point)) {
                    ret[Point(x, y)] = organisms.find(Point(x, y))->second;
                }
            }
        }
        return ret;
    }
    
    void update() {
        removeDead();
    }
    
    void removeDead() {
        for (Pair org : organisms) {
            if (org.second->isDead()) {
                organisms.erase(org.second->getLocation());
            }
        }
    }
    

    bool inBounds(Point point) const {
        return !(point.x >= width || point.x < 0 || point.y >= height || point.y < 0);
    }
    
    void addOrganism(Organism* org) {
        if (spaceIsClear(org -> getLocation())) {
            organisms[org->getLocation()] = org;
        }
    }
    
    void addOrganism(Organism org) {
        if (spaceIsClear(org.getLocation())) {
            organisms[org.getLocation()] = &org;
        }
    }
    
    void removeObject(Point* point) {
        if (organisms.find(*point) != organisms.end()) {
            organisms.erase(*point);
        }
    }
};



#endif /* World_h */
