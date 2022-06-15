//
// Created by hanm on 22-6-15.
//

#include "KDTree.h"

Point KDTree::max_point() {
    return root_->max_point;
}

void KDTree::update_distance(const Point &ref_point) {
    root_->send_delay_point(ref_point);
    root_->update_distance(memory_ops, mult_ops);
}

void KDTree::sample(const int sample_num) {
    Point ref_point;
    for (int i = 1; i < sample_num; i++) {
        ref_point = max_point();
        sample_points.push_back(ref_point);
        update_distance(ref_point);
    }
}

bool KDTree::leftNode(int high, int count) {
    return count == 1;
}

KDTree::KDTree(KDTreeBase::Points &data) : KDTreeBase(data) {

}

void KDTree::addNode(KDTreeBase::NodePtr p) {

}