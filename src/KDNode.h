//
// Created by 韩萌 on 2022/6/14.
//

#ifndef KD_TREE_BASED_FARTHEST_POINT_SAMPLING_KDNODE_H
#define KD_TREE_BASED_FARTHEST_POINT_SAMPLING_KDNODE_H
#include "Point.h"
#include "vector"
#include "queue"
#include "Interval.h"

using namespace std;

class KDNode {
public:
    typedef Point* Points;
    Points points;
    int pointLeft, pointRight;
    int idx;

    Interval bbox[3];
    std::vector<Point> waitpoints;
    std::vector <Point> delaypoints;
    Point max_point;
    KDNode *left;
    KDNode *right;

    KDNode();

    KDNode(const KDNode &a);

    void init(const Point &ref);

    void updateMaxPoint(const Point &lpoint, const Point &rpoint);

    float bound_distance(const Point &ref_point);

    void send_delay_point(const Point &point) ;

    void update_distance(int &memory_ops, int &mult_ops) ;

    void reset();

    int size();
};


#endif //KD_TREE_BASED_FARTHEST_POINT_SAMPLING_KDNODE_H
