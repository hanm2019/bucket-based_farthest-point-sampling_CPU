//
// Created by 韩萌 on 2022/6/14.
//

#ifndef KD_TREE_BASED_FARTHEST_POINT_SAMPLING_POINT_H
#define KD_TREE_BASED_FARTHEST_POINT_SAMPLING_POINT_H

#include "cmath"
#include "iostream"

class Point {
public:
    double pos[3]; // x, y, z
    double dis;
    int id;

    bool operator<(const Point &aii) const ;
    Point();
    Point(double x, double y, double z, double dis, int id);
    Point(const Point &obj);
    ~Point();
    friend std::ostream &operator<<(std::ostream &out, const Point &A) {
        out << "Point: [" << A.pos[0] << ", " << A.pos[1] << ", " << A.pos[2] << "]  id:" << A.id  << "dist:" << A.dis;
        return out;
    }
    inline double operator[](int i) const{
        return pos[i];
    }

    double distance(const Point &b) ;

    void reset();

    double updatedistance(const Point &ref) ;
};


#endif //KD_TREE_BASED_FARTHEST_POINT_SAMPLING_POINT_H
