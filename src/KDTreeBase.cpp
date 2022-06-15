//
// Created by 韩萌 on 2022/6/14.
//

#include "KDTreeBase.h"
KDTreeBase::KDTreeBase(Points &data) : memory_ops(0), mult_ops(0), root_(nullptr) {
    points_ = data;
}

KDTreeBase::~KDTreeBase() {
    deleteNode(root_);
}

void KDTreeBase::deleteNode(NodePtr node_p) {
    if (node_p->left) deleteNode(node_p->left);
    if (node_p->right) deleteNode(node_p->right);
    delete node_p;
}

void KDTreeBase::buildKDtree() {
    std::vector <Interval> bbox;
    std::vector <Interval> *bbox_ptr = NULL;
    int left = 0;
    int right = points_.size() - 1;
    computeBoundingBox(left, right, bbox);
    bbox_ptr = &bbox;
    root_ = divideTree(left, right, bbox_ptr, 0);
}

KDNode * KDTreeBase::get_root() { return root_; }

KDNode * KDTreeBase::divideTree(int left, int right, std::vector <Interval> *bbox_ptr, int curr_high) {
    NodePtr node = new KDNode();
    node->bbox = *bbox_ptr;
    int count = right - left;
    if(leftNode(curr_high,count)){
        node->left = nullptr;
        node->right = nullptr;
        node->points.assign(points_.begin() + left, points_.begin() + right + 1);
        addNode(node);
        return node;
    } else {
        int split_dim = 0;
        double split_val = 0.0;
        std::vector<double> value_list(count+1);
        findSplitDim(split_dim, bbox_ptr);

        getValueList(left, right, split_dim, value_list);
        std::vector<double> *value_list_ptr = &value_list;
        qSelectMedian(value_list_ptr, split_val);
        value_list.clear();
        value_list.resize(0);
        int lim1 = 0, lim2 = 0, split_delta;
        planeSplit(left, right, split_dim, split_val, lim1, lim2);
        split_delta = (lim1 + lim2) / 2;
        std::vector <Interval> bbox_l;
        std::vector <Interval> bbox_r;
        computeBoundingBox(left, left + split_delta, bbox_l);
        computeBoundingBox(left + split_delta + 1, right, bbox_r);
        node->left = divideTree(left, left + split_delta, &bbox_l, curr_high + 1);
        node->right = divideTree(left + split_delta + 1, right, &bbox_r, curr_high + 1);
        return node;
    }
}

void KDTreeBase::planeSplit(int left, int right, int split_dim,
                            float split_val, int &lim1, int &lim2) {
    int start = 0;
    int end = right - left;

    for (;;) {
        while (start <= end && points_[left + start][split_dim] < split_val)
            ++start;
        while (start <= end && points_[left + end][split_dim] >= split_val)
            --end;

        if (start > end) break;
        std::swap(points_[left + start], points_[left + end]);
        ++start;
        --end;
    }
    lim1 = start;

    end = right - left;
    for (;;) {
        while (start <= end && points_[left + start][split_dim] <= split_val)
            ++start;
        while (start <= end && points_[left + end][split_dim] > split_val)
            --end;
        if (start > end) break;
        std::swap(points_[left + start], points_[left + end]);
        ++start;
        --end;
    }
    lim2 = end;
}

void KDTreeBase::getValueList(int left, int right, int split_dim, std::vector<double> &value_list) {
    for (int i = left; i <= right; i++)
        value_list.push_back(points_[i][split_dim]);
}

void KDTreeBase::qSelectMedian(std::vector<double> *value_list, double &median_value) {
    double sum = 0;
    for(auto value:*value_list){
        sum += value;
    }
    median_value = sum / value_list->size();
}


void KDTreeBase::findSplitDim(int &best_dim, std::vector <Interval> *bbox_ptr) {

    double min_ ,max_ ;
    double span = 0.0;

    for (int cur_dim = 0; cur_dim < bbox_ptr->size(); cur_dim++) {
        min_ = (*bbox_ptr)[cur_dim].low;
        max_ = (*bbox_ptr)[cur_dim].high;

        if ((max_ - min_) > span) {
            best_dim = cur_dim;
            span = (max_ - min_);
        }
    }
}

void KDTreeBase::computeBoundingBox(int left, int right, std::vector <Interval> &bbox) {
    int cur_dim = 0;
    for (; cur_dim < 3; cur_dim++) {
        Interval bounds;
        computeMinMax(left, right, cur_dim, bounds);
        bbox.push_back(bounds);
    }
}

void KDTreeBase::computeMinMax(int left, int right, int dim, Interval &bound) {
    double min_val = points_[left][dim];
    double max_val = points_[left][dim];
    for (int i = left + 1; i <= right; ++i) {

        double val = points_[i][dim];

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