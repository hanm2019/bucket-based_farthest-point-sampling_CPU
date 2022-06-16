//
// Created by 韩萌 on 2022/6/14.
//

#include "KDTreeBase.h"
KDTreeBase::KDTreeBase(Points &data) : memory_ops(0), mult_ops(0), root_(nullptr) {
    points_ = data;
}

KDTreeBase::~KDTreeBase() {
    if(root_!= nullptr) deleteNode(root_);
}

void KDTreeBase::deleteNode(NodePtr node_p) {
    if (node_p->left) deleteNode(node_p->left);
    if (node_p->right) deleteNode(node_p->right);
    delete node_p->points;
    delete node_p;
}

void KDTreeBase::buildKDtree() {
    std::vector <Interval> bbox(3);
    int left = 0;
    int right = points_.size() - 1;
    computeBoundingBox(left, right, bbox);
    root_ = divideTree(left, right, bbox, 0);
}

KDNode * KDTreeBase::get_root() { return root_; }

KDNode * KDTreeBase::divideTree(int left, int right, std::vector <Interval> &bbox_ptr, int curr_high) {
    NodePtr node = new KDNode();
    node->bbox = bbox_ptr;
    int count = right - left;
    if(leftNode(curr_high,count)){
        node->points = new std::vector<Point>(points_.begin() + left, points_.begin() + right + 1);
        addNode(node);
        return node;
    } else {
        int split_dim = 0;
        float split_val = 0.0;
        findSplitDim(split_dim, bbox_ptr);
        qSelectMedian(split_dim, left, right, split_val);

        int lim1 = 0, lim2 = 0, split_delta;
        planeSplit(left, right, split_dim, split_val, lim1, lim2);
        split_delta = (lim1 + lim2) / 2;
        if(split_delta < 0) split_delta = 0;
        if(split_delta > (right - left - 1)) split_delta = (right - left - 1);
        std::vector <Interval> bbox_cur(bbox_ptr);
        computeBoundingBox(left, left + split_delta, bbox_cur,split_dim);
        node->left = divideTree(left, left + split_delta, bbox_cur, curr_high + 1);
        computeBoundingBox(left + split_delta + 1, right, bbox_cur,split_dim);
        node->right = divideTree(left + split_delta + 1, right, bbox_cur, curr_high + 1);
        return node;
    }
}

void KDTreeBase::planeSplit(int left, int right, int split_dim,
                            float split_val, int &lim1, int &lim2) {
    int start = left;
    int end = right;

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

    end = right;
    for (;;) {
        while (start <= end && points_[start].pos[split_dim] <= split_val)
            ++start;
        while (start <= end && points_[end].pos[split_dim] > split_val)
            --end;
        if (start > end) break;
        std::swap(points_[start], points_[end]);
        ++start;
        --end;
    }
    lim2 = end - left;
}


void KDTreeBase::qSelectMedian(int dim, int left, int right , float &median_value) {
    float sum = 0;
    for (int i = left; i <= right; i++)
        sum += points_[i].pos[dim];
    median_value = sum / (right - left + 1);
}


void KDTreeBase::findSplitDim(int &best_dim, std::vector <Interval> &bbox_ptr) {

    float min_ ,max_ ;
    float span = 0.0;

    for (int cur_dim = 0; cur_dim < bbox_ptr.size(); cur_dim++) {
        min_ = (bbox_ptr)[cur_dim].low;
        max_ = (bbox_ptr)[cur_dim].high;

        if ((max_ - min_) > span) {
            best_dim = cur_dim;
            span = (max_ - min_);
        }
    }
}

inline void KDTreeBase::computeBoundingBox(int left, int right, std::vector <Interval> &bbox) {
    float min_val_0 = points_[left][0];
    float max_val_0 = points_[left][0];
    float min_val_1 = points_[left][1];
    float max_val_1 = points_[left][1];
    float min_val_2 = points_[left][2];
    float max_val_2 = points_[left][2];

    float val_0,val_1,val_2;
    for (int i = left + 1; i <= right; ++i) {
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
    bbox[0].high = max_val_0;
    bbox[0].low = min_val_0;

    bbox[1].high = max_val_1;
    bbox[1].low = min_val_1;

    bbox[2].high = max_val_2;
    bbox[2].low = min_val_2;

}

inline void KDTreeBase::computeBoundingBox(int left, int right, vector<Interval> &bbox, int dim) {
    computeMinMax(left, right, dim, bbox[dim]);
}

inline void KDTreeBase::computeMinMax(int left, int right, int dim, Interval &bound) {
    float min_val = points_[left][dim];
    float max_val = points_[left][dim];
    for (int i = left + 1; i <= right; ++i) {

        float val = points_[i][dim];

        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
    }
    bound.high = max_val;
    bound.low = min_val;
}

void KDTreeBase::init(const Point &ref) {
    sample_points.clear();
    sample_points.push_back(ref);
    root_->init(ref);
}

void KDTreeBase::cout_sample() {
    for (const Point &p: sample_points) {
        std::cout << p;
    }
}

int KDTreeBase::verify() {
    int idsum = 0;
    for(const auto s:sample_points){idsum += s.id;}
    return idsum;
}


