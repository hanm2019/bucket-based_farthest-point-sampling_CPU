//
// Created by 韩萌 on 2022/6/14.
//
#include<cstdio>
#include<iostream>
#include<fstream>
#include "Point.h"
#include "vector"
#include "ctime"

int main(int argc,char** argv) {
    if (argc != 3) {
        printf("please run this program by the following parameter: sample_number filePath\n");
        return 0;
    }
    int sample_number = atoi(argv[1]);
    std::string filename = argv[2];

    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "file not exist" << std::endl;
        return 0;
    }

    std::vector <Point> point_data;
    int count = 0;
    if (fin.is_open()) {
        float xx, yy, zz;
        while (fin >> xx >> yy >> zz) {
            point_data.emplace_back(xx, yy, zz, 10000000, count);
            count++;
        }
    }
    fin.close();
    const int pointSize = point_data.size();
    auto points = (Point*)malloc(pointSize* sizeof(Point));
    for(int i = 0; i < pointSize;i++){
        points[i] = point_data[i];
    }
    printf("Total:%d\n", pointSize);
    auto samplePoints = (Point*) malloc(sample_number*sizeof(Point));

    Point init_point = points[0];
    clock_t start_t, end_t;
    start_t = clock();
    Point ref_point;
    ref_point = init_point;
    samplePoints[0] = ref_point;
    float dis, max_dis;
    Point max_point;
    for (int i = 1; i < sample_number; i++) {
        max_dis = 0;
#ifdef METRICS
	int updateDistanceCount = 0;
#endif
        for(int j = 0; j < pointSize; j++){

#ifdef METRICS
            dis = points[j].updateDistanceAndCount(ref_point, updateDistanceCount);
#else
            dis = points[j].updatedistance(ref_point);
#endif
            if (dis > max_dis) {
                max_dis = dis;
                max_point = points[j];
            }
        }
#ifdef METRICS
        printf("%d:%d\n", i, updateDistanceCount);
#endif
        ref_point = max_point;
        samplePoints[i] = ref_point;
    }

#ifndef  METRICS
    end_t = clock();
    std::cout << "Report:" << std::endl;
    std::cout << "    Type   :Baseline" << std::endl;
    std::cout << "    Points :" << pointSize << std::endl;
    std::cout << "    NPoint :" << sample_number << std::endl;
    std::cout << "    RunTime:" << (double) (end_t - start_t) << "us" << std::endl;
    long checkCode = 0;
    for(int i = 0;i < sample_number; i++){checkCode += samplePoints[i].id;}
    std::cout << "    Check  :" << checkCode << std::endl;
    std::cout << "    Param  :" << filename << std::endl;
    std::time_t result = std::time(nullptr);
    std::cout << "  Timestamp:" << std::asctime(std::localtime(&result)) << std::endl;
#endif
    free(points);
}
