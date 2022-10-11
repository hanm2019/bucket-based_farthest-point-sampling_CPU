//
// Created by 韩萌 on 2022/6/14.
//

#ifndef KD_TREE_BASED_FARTHEST_POINT_SAMPLING_POINT_H
#define KD_TREE_BASED_FARTHEST_POINT_SAMPLING_POINT_H

#include "cmath"
#include "iostream"
#include "utils.h"

class Point {
public:
    float pos[3]{}; // x, y, z
    float dis;
    int id;

    bool operator<(const Point &aii) const ;
    Point();
    Point(float x, float y, float z, float dis, int id);
    Point(const Point &obj);
    ~Point();
    friend std::ostream &operator<<(std::ostream &out, const Point &A) {
        out << "Point: [" << A.pos[0] << ", " << A.pos[1] << ", " << A.pos[2] << "]  id:" << A.id  << "dist:" << A.dis;
        return out;
    }
    inline float operator[](int i) const{
        return pos[i];
    }

    float distance(const Point &b) ;

    void reset();

    float updatedistance(const Point &ref) ;

    float updateDistanceAndCount(const Point &ref, int &count);
};


#endif //KD_TREE_BASED_FARTHEST_POINT_SAMPLING_POINT_H
