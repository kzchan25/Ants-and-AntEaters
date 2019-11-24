#ifndef Controller_h
#define Controller_h

#include <vector>
#include <time.h>
#include <unordered_map>
#include "Point.h"
#include "Organism.h"
#include "World.h"
#include "Ant.h"
#include "AntEater.h"
#include "View.h"

typedef pair<const Point, Organism*> Pair;

class Controller {
    const int ANT_SPAWN_PERCENTAGE = 30;
    const int ANTEATER_SPAWN_PERCENTAGE = 2;
    
    World world;
public:
    Controller(int width, int height) { //setup
        srand(time(NULL));
        world = World(width, height);
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int random = (int)(((double)(rand())/(RAND_MAX)) * 100);
                if (random<= ANTEATER_SPAWN_PERCENTAGE) {
                    world.addOrganism(new AntEater(Point(x, y)));
                }
                else if (random <= ANT_SPAWN_PERCENTAGE) {
                    world.addOrganism(new Ant(Point(x, y)));
                }
            }
        }
        View::draw(world.getOrganisms(), world.getWidth(), world.getHeight());
        loop();
    }
    
    void loop() {
        int iterations = 0;
        while(!world.full() && !world.empty()) {
            cin.get();
            world.update();
            updateOrganisms();
            updateAntEaters();
            reproduce();
            world.removeDead();
            View::draw(world.getOrganisms(), world.getWidth(), world.getHeight());
            iterations++;
            cout << "Iterations: " << iterations << endl;
        }
    }
    
    void reproduce() {
        for (Pair o : *world.getOrganisms()) {
            if (o.second -> reproduceFlag()) {
                if (o.second -> adjacentSpaceIsClear(o.second->getLocation(), world.getAroundPoint(o.first, 1))) {
                    Point point = o.second -> adjacentSpace(o.first, world.getAroundPoint(o.first, 1), world.getWidth(), world.getHeight());
                    if (o.second -> getChar() == "a" && world.spaceIsClear(point)) {
                        world.addOrganism(new Ant(point));
                    }
                    if (o.second -> getChar() == "@" && world.spaceIsClear(point)) {
                        world.addOrganism(new AntEater(point));
                    }
                }
            }
        }
    }
    
    void updateOrganisms() {
        int moved = 0;
        while (moved < world.getOrganisms() -> size()) {
            for (Pair o : *world.getOrganisms()) {
                if (!o.second -> getMoved()) {
                    Point from = o.first;
                    Point to = o.second -> move((world.getAroundPoint(from, 1)), world.getWidth(), world.getHeight());
                    o.second -> setMoved(true);
                    world.move(from, to, o.second);
                }
            }
            moved = 0;
            for (Pair o : *world.getOrganisms()) {
                if (o.second -> getMoved()) {
                    moved++;
                }
            }
        }
        for (Pair o : *world.getOrganisms()) {
            if (o.second -> getMoved()) {
                o.second -> setMoved(false);
            }
        }
    }
    
    void updateAntEaters() {
        vector<AntEater*> antEaters;
        for (Pair i : *world.getOrganisms()) {
            if (i.second -> getChar() == "@"){
                AntEater* antEater = (static_cast<AntEater*>(i.second));
                antEaters.push_back(antEater);
            }
        }
        for (int i = 0; i < antEaters.size(); i++) {
            Point* antLocation = antEaters[i]->eat(&world.getAroundPoint(antEaters[i]->getPoint(), 5));
            if (antLocation != nullptr) {
                world.removeObject(antLocation);
            }
        }
    }
    
    static void printMap(unordered_map<Point, Organism*,PointHasher>* orgs) {
        for (Pair i : *orgs) {
            cout << i.second -> getChar() << "  " << i.first.x << ", " << i.first.y << endl;
        }
        cout << endl;
    }
    
    
    
};

#endif /* Controller_h */
