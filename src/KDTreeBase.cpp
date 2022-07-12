//
// Created by 韩萌 on 2022/6/14.
//

#include <cstring>
#include "KDTreeBase.h"
KDTreeBase::KDTreeBase(Points &data,int pointSize, Points &samplePoints) : pointSize(pointSize), memory_ops(0), mult_ops(0),sample_points(samplePoints),root_(nullptr),points_(data){
}

KDTreeBase::~KDTreeBase() {
    if(root_!= nullptr) deleteNode(root_);
}

void KDTreeBase::deleteNode(NodePtr node_p) {
    if (node_p->left) deleteNode(node_p->left);
    if (node_p->right) deleteNode(node_p->right);
    delete node_p;
}

void KDTreeBase::buildKDtree() {
    Interval bbox[DIM];
    int left = 0;
    int right = pointSize;
    computeBoundingBox(left, right, bbox);
    root_ = divideTree(left, right, bbox, 0);
}

KDNode * KDTreeBase::get_root() { return root_; }

KDNode * KDTreeBase::divideTree(int left, int right, Interval (&bbox_ptr)[DIM], int curr_high) {
    //printf("high: %d point[%d-%d), \n",curr_high, left, right );
    NodePtr node = new KDNode();
    //printf("nodeptr and node size:%d %d\n", sizeof(node), sizeof(*node));
    memcpy(node->bbox, bbox_ptr, DIM*sizeof(Interval));

    int count = right - left;
    if(leftNode(curr_high,count)){
        node->pointLeft = left;
        node->pointRight = right;
        node->points = this->points_;
        //node->points = new std::vector<Point>(points_.begin() + left, points_.begin() + right + 1);
        addNode(node);
        return node;
    } else {
        int split_dim = 0;
        float split_val = 0.0;
        findSplitDim(split_dim, bbox_ptr);
        qSelectMedian(split_dim, left, right, split_val);

        int  split_delta;
        planeSplit(left, right, split_dim, split_val, split_delta);

        Interval bbox_cur[3];
        computeBoundingBox(left, left + split_delta, bbox_cur);
        node->left = divideTree(left, left + split_delta, bbox_cur, curr_high + 1);
        computeBoundingBox(left + split_delta, right, bbox_cur);
        node->right = divideTree(left + split_delta, right, bbox_cur, curr_high + 1);
        return node;
    }
}

void KDTreeBase::planeSplit(int left, int right, int split_dim,
                            float split_val, int &lim1) {
    int start = left;
    int end = right - 1;

    for (;;) {
        while (start <= end && points_[start].pos[split_dim] < split_val)
            ++start;
        while (start <= end && points_[end].pos[split_dim] >= split_val)
            --end;

        if (start > end) break;
        std::swap(points_[start], points_[end]);
        ++start;
        --end;
    }
    lim1 = start - left;
    if(start == left) lim1 = 1;
    if(start == right) lim1 = (right - left - 1);
}


void KDTreeBase::qSelectMedian(int dim, int left, int right , float &median_value) {
    float sum = 0;
    for (int i = left; i < right; i++)
        sum += points_[i].pos[dim];
    median_value = sum / (right - left);
}


void KDTreeBase::findSplitDim(int &best_dim, Interval (&bbox_ptr)[DIM]) {

    float min_ ,max_ ;
    float span = 0.0;

    for (size_t cur_dim = 0; cur_dim < DIM; cur_dim++) {
        min_ = (bbox_ptr)[cur_dim].low;
        max_ = (bbox_ptr)[cur_dim].high;

        if ((max_ - min_) > span) {
            best_dim = (int)cur_dim;
            span = (max_ - min_);
        }
    }
}

inline void KDTreeBase::computeBoundingBox(int left, int right, Interval (&bbox_ptr)[3]) {
    float min_val_0 = points_[left][0];
    float max_val_0 = points_[left][0];
    float min_val_1 = points_[left][1];
    float max_val_1 = points_[left][1];
    float min_val_2 = points_[left][2];
    float max_val_2 = points_[left][2];

    float val_0,val_1,val_2;
    for (int i = left + 1; i < right; ++i) {
        float* pos = points_[i].pos;
        val_0 = pos[0];
        val_1 = pos[1];
        val_2 = pos[2];

        if (val_0 < min_val_0) min_val_0 = val_0;
        if (val_0> max_val_0) max_val_0 = val_0;

        if (val_1 < min_val_1) min_val_1 = val_1;
        if (val_1> max_val_1) max_val_1 = val_1;

        if (val_2 < min_val_2) min_val_2 = val_2;
        if (val_2> max_val_2) max_val_2 = val_2;
    }
    bbox_ptr[0].high = max_val_0;
    bbox_ptr[0].low = min_val_0;

    bbox_ptr[1].high = max_val_1;
    bbox_ptr[1].low = min_val_1;

    bbox_ptr[2].high = max_val_2;
    bbox_ptr[2].low = min_val_2;

}


inline void KDTreeBase::computeMinMax(int left, int right, int dim, Interval &bound) {
    float min_val = points_[left][dim];
    float max_val = points_[left][dim];
    for (int i = left + 1; i < right; ++i) {

        float val = points_[i][dim];

        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
    }
    bound.high = max_val;
    bound.low = min_val;
}

void KDTreeBase::init(const Point &ref) {
    sample_points[0]=ref;
    root_->init(ref);
}

void KDTreeBase::cout_sample(int sampleSize) {
    for(int i = 0 ;i < sampleSize;i++){
        std::cout << sample_points[i];
    }
}

int KDTreeBase::verify(int sampleSize) {
    int idsum = 0;
    for(int i = 0 ; i < sampleSize;i++){
        idsum += sample_points[i].id;
    }
    return idsum;
}


