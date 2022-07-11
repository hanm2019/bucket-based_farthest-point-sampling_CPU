//
// Created by hanm on 22-6-15.
//

#ifndef FPS_CPU_KDTREE_H
#define FPS_CPU_KDTREE_H

#include "KDTreeBase.h"

class KDTree :public KDTreeBase{
public:

    explicit KDTree(KDTreeBase::Points &data, int pointSize, KDTreeBase::Points &samplePoints);

    Point max_point() override;

    void update_distance(const Point &ref_point) override;

    void sample(int sample_num) override;

    bool leftNode(int high, int count) override;

    void addNode(NodePtr p) override;
};


#endif //FPS_CPU_KDTREE_H
