#ifndef PointHasher_h
#define PointHasher_h

class PointHasher {
public:
    size_t operator() (const Point& point) const {
        size_t prime = 31;
        size_t result = 1;
        result = prime * result + point.x;
        result = prime * result + point.y;
        return result;
    }
};

#endif /* PointHasher_h */
