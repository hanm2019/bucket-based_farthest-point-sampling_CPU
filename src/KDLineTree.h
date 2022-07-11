//
// Created by hanm on 22-6-15.
//

#ifndef FPS_CPU_KDLINETREE_H
#define FPS_CPU_KDLINETREE_H

#include "KDTreeBase.h"
class KDLineTree :public KDTreeBase{
public:

    KDLineTree(KDTreeBase::Points &data, int pointSize, int treeHigh, KDTreeBase::Points &samplePoints);
    ~KDLineTree();
    std::vector<NodePtr> KDNode_list;

    int high_;

    Point max_point() override;

    void update_distance(const Point &ref_point) override;

    void sample(int sample_num) override;

    bool leftNode(int high, int count) override;

    void addNode(NodePtr p) override;
};


#endif //FPS_CPU_KDLINETREE_H
