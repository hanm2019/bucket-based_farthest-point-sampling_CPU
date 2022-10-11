//
// Created by 韩萌 on 2022/6/14.
//

#include "KDNode.h"
KDNode::KDNode() :points(nullptr), pointLeft(0),pointRight(0), max_point(),left(nullptr),right(nullptr) {
}

KDNode::KDNode(const KDNode &a) {
    points = a.points;
    pointLeft = a.pointLeft;
    pointRight = a.pointRight;
    delaypoints = a.delaypoints;
    max_point = a.max_point;
    left = a.left;
    right = a.right;
}

void KDNode::init(const Point &ref) {
    waitpoints.clear();
    delaypoints.clear();
    if (this->left && this->right) {
        this->left->init(ref);
        this->right->init(ref);
        updateMaxPoint(this->left->max_point, this->right->max_point);
    } else {
        float dis;
        float maxdis(-1);
        for(int i = pointLeft; i < pointRight; i++){
            dis = points[i].updatedistance(ref);
            if (dis > maxdis) {
                maxdis = dis;
                max_point = points[i];
            }
        }
    }
}

void KDNode::updateMaxPoint(const Point &lpoint, const Point &rpoint) {

    if (lpoint.dis > rpoint.dis) this->max_point = lpoint;
    else this->max_point = rpoint;
}

float KDNode::bound_distance(const Point &ref_point) {
    float bound_dis(0);
    float dim_distance;
    for (int cur_dim = 0; cur_dim < 3; cur_dim++) {
        dim_distance = 0;
        if (ref_point[cur_dim] > bbox[cur_dim].high) dim_distance = ref_point[cur_dim] - bbox[cur_dim].high;
        if (ref_point[cur_dim] < bbox[cur_dim].low) dim_distance = bbox[cur_dim].low - ref_point[cur_dim];
        bound_dis += pow2(dim_distance);
    }
    return bound_dis;
}

void KDNode::send_delay_point(const Point &point) {
    this->waitpoints.push_back(point);
}

void logging(int idx, int pointSize){
    printf("Calculate Bucket:%d, size:%d\n", idx, pointSize);
}

void KDNode::update_distance(int &memory_ops, int &mult_ops) {
    for(const auto& ref_point: this->waitpoints){
        float lastmax_distance = this->max_point.dis;
        float cur_distance = this->max_point.distance(ref_point);
        mult_ops++;
        // cur_distance > lastmax_distance意味着当前Node的max_point不会进行更新
        if (cur_distance > lastmax_distance) {
            float boundary_distance = bound_distance(ref_point);
            mult_ops++;
            if (boundary_distance < lastmax_distance) {
                this->delaypoints.push_back(ref_point);
#ifdef NOMAPPING

#ifndef MERGESIZE
    #define MERGESIZE 4
#endif
                if(this->delaypoints.size() >= MERGESIZE){
                    //logging(this->idx, pointRight - pointLeft);
                    float dis;
                    float maxdis;
                    for (const auto &delay_point: delaypoints) {
                        maxdis = -1;
                        for(int i = pointLeft; i < pointRight; i++){
                            dis = points[i].updatedistance(delay_point);
                            if (dis > maxdis) {
                                maxdis = dis;
                                max_point = points[i];
                            }
                        }
                    }
                    this->delaypoints.clear();
                }
#endif
            }
        } else {
            if (this->right && this->left) {
                if(!delaypoints.empty()){
                    for (const auto &delay_point: delaypoints) {
                        this->left->send_delay_point(delay_point);
                        this->right->send_delay_point(delay_point);
                    }
                    delaypoints.clear();
                }
                this->left->send_delay_point(ref_point);
                this->left->update_distance(memory_ops, mult_ops);

                this->right->send_delay_point(ref_point);
                this->right->update_distance(memory_ops, mult_ops);

                updateMaxPoint(this->left->max_point, this->right->max_point);
            } else {
                //logging(this->idx, pointRight - pointLeft);
                float dis;
                float maxdis;
                this->delaypoints.push_back(ref_point);
                for (const auto &delay_point: delaypoints) {
                    maxdis = -1;
                    for(int i = pointLeft; i < pointRight; i++){
                        dis = points[i].updatedistance(delay_point);
                        if (dis > maxdis) {
                            maxdis = dis;
                            max_point = points[i];
                        }
                    }
                }
                mult_ops += delaypoints.size() * (pointRight - pointLeft);
                memory_ops += (pointRight - pointLeft);
                this->delaypoints.clear();
            }
        }
    }
    this->waitpoints.clear();
}

void KDNode::reset() {
    for(int i = pointLeft; i < pointRight;i++){
        points[i].reset();
    }
    this->waitpoints.clear();
    this->delaypoints.clear();
    this->max_point.reset();
    if(this->left && this->right){
        this->left->reset();
        this->right->reset();
    }
}

int KDNode::size() {
    if(this->left && this->right)
        return this->left->size() + this->right->size();
    return (pointRight - pointLeft);
}
