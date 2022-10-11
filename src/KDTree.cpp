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
#ifdef METRICS
    int pre_memory_ops = 0;
#endif
    for (int i = 1; i < sample_num; i++) {
        ref_point = max_point();
        sample_points[i] = ref_point;
        update_distance(ref_point);
#ifdef METRICS
	printf("%d:%d\n", i, memory_ops - pre_memory_ops);
	pre_memory_ops = memory_ops;
#endif
    }
}

bool KDTree::leftNode(int high, int count) {
    return count == 1;
}

KDTree::KDTree(KDTreeBase::Points &data, int pointSize, KDTreeBase::Points &samplePoints) : KDTreeBase(data,pointSize, samplePoints) {

}

void KDTree::addNode(KDTreeBase::NodePtr p) {

}
