//
// Created by 韩萌 on 2022/6/14.
//

#include "Point.h"

bool Point::operator<(const Point &aii) const {
    return dis < aii.dis;
}

float Point::distance(const Point &b) {
    return pow2((this->pos[0] - b.pos[0])) +
           pow2((this->pos[1] - b.pos[1])) +
           pow2((this->pos[2] - b.pos[2]));
}

float Point::updatedistance(const Point &ref) {
    this->dis = std::min(this->dis, distance(ref));
    return this->dis;
}

float Point::updateDistanceAndCount(const Point &ref, int &count) {
    float tempDistance = distance(ref);
    if(tempDistance < this->dis) {
        this->dis = tempDistance;
        count++;
    }
    return this->dis;
}

Point::Point() {
    this->dis = 1e20;
    this->pos[0] = 0;
    this->pos[1] = 0;
    this->pos[2] = 0;
    this->id = 0;
}

Point::~Point() = default;

Point::Point(float x, float y, float z, float dis, int id) {
    this->dis = dis;
    this->pos[0] = x;
    this->pos[1] = y;
    this->pos[2] = z;
    this->id = id;
}

void Point::reset() {
    this->dis = 1e20;

}

Point::Point(const Point &obj) {
    this->pos[0] = obj.pos[0];
    this->pos[1] = obj.pos[1];
    this->pos[2] = obj.pos[2];
    this->dis = obj.dis;
    this->id = obj.id;
}
