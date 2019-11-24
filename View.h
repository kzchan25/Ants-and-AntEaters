#ifndef View_h
#define View_h
#include "Controller.h"

class View {
public:
    static void draw(unordered_map<Point, Organism*, PointHasher>* organisms, int width, int height) {
        string map = "";
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (organisms -> find(Point(x, y)) != organisms -> end()) {
                    map += " " + organisms -> find(Point(x, y)) -> second->getChar();
                }
                else {
                    map += " -";
                }
            }
            map += "\n";
        }
        cout << map << endl;
        cout << "Organisms: " << organisms->size() << endl
        << "Ants: " << getAnts(organisms) << endl
        << "AntEaters: " << getAntEaters(organisms) << endl;
    }
    
private:
    static int getAnts(unordered_map<Point, Organism*, PointHasher>* organisms) {
        int ants = 0;
        for (Pair o : *organisms) {
            if (o.second -> getChar() == "a") {
                ants++;
            }
        }
        return ants;
    }
    
    static int getAntEaters(unordered_map<Point, Organism*, PointHasher>* organisms) {
        int antEaters = 0;
        for (Pair o : *organisms) {
            if (o.second -> getChar() == "@") {
                antEaters++;
            }
        }
        return antEaters;
    }
};


#endif /* View_h */
