//
// Created by 韩萌 on 2022/6/14.
//
#include<cstdio>
#include<iostream>
#include<fstream>
#include "Point.h"
#include "vector"

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
    std::vector <Point> sample_points;
    int count = 0;
    if (fin.is_open()) {
        float xx, yy, zz;
        while (fin >> xx >> yy >> zz) {
            point_data.push_back({xx, yy, zz, 10000000, count});
            count++;
        }
    }
    fin.close();
    Point init_point = point_data[0];
    clock_t start_t, end_t;
    start_t = clock();
    Point ref_point;
    ref_point = init_point;
    float dis, max_dis;
    Point max_point;
    for (int i = 0; i < sample_number; i++) {
        max_dis = 0;
        for (auto &p: point_data) {
            dis = p.updatedistance(ref_point);
            if (dis > max_dis) {
                max_dis = dis;
                max_point = p;
            }
        }
        ref_point = max_point;
        sample_points.push_back(ref_point);
    }

    end_t = clock();
    std::cout << "Report:" << std::endl;
    std::cout << "    Type  :Baseline" << std::endl;
    std::cout << "    Points:" << point_data.size() << std::endl;
    std::cout << "    NPoint:" << sample_number << std::endl;
    std::cout << "    Time  :" << (double) (end_t - start_t) << "us" << std::endl;
    int idsum = 0;
    for(const auto& s:sample_points){idsum += s.id;}
    std::cout << "id sum:" << idsum << std::endl;
}
