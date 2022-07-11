//
// Created by hanm on 22-6-15.
//

#include "KDLineTree.h"

Point KDLineTree::max_point() {
    Point tmpPoint;
    float max_distance = 0;
    for(const auto& bucket : KDNode_list){
        if(bucket->max_point.dis > max_distance){
            max_distance = bucket->max_point.dis;
            tmpPoint = bucket->max_point;
        }
    }
    return tmpPoint;
}

void KDLineTree::update_distance(const Point &ref_point) {
    for(const auto& bucket : KDNode_list){
        bucket->send_delay_point(ref_point);
        bucket->update_distance(memory_ops, mult_ops);
    }
}

void KDLineTree::sample(const int sample_num) {
    Point ref_point;

    for (int i = 1; i < sample_num; i++) {
        ref_point = max_point();
        sample_points[i] = ref_point;
        update_distance(ref_point);
    }
}

bool KDLineTree::leftNode(int high, int count) {
    return high == high_ || count == 0;
}

KDLineTree::KDLineTree(KDTreeBase::Points &data, int pointSize, int treeHigh,KDTreeBase::Points &samplePoints) : KDTreeBase(data,pointSize, samplePoints),high_(treeHigh) {
    KDNode_list.clear();
}

KDLineTree::~KDLineTree(){
    KDNode_list.clear();
}

void KDLineTree::addNode(KDTreeBase::NodePtr p) {
    KDNode_list.push_back(p);
}
