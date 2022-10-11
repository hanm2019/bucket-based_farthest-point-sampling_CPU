#include<cstdio>
#include<iostream>
#include<fstream>
#include<vector>
#include "ctime"
#include "Point.h"
#ifdef LINE
#include "KDLineTree.h"
#else
#include "KDTree.h"
#endif

int main(int argc, char **argv) {
#ifdef LINE
   if (argc != 4) {
        printf("please run this program by the following parameter:kd_tree_high sample_number filePath\n");
        return 0;
    }
    int kd_height = atoi(argv[1]);
    int sample_number = atoi(argv[2]);
    std::string filename =  argv[3];
#else
    if (argc != 3) {
        printf("please run this program by the following parameter: sample_number filePath\n");
        return 0;
    }
    int sample_number = atoi(argv[1]);
    std::string filename =  argv[2];
#endif
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "file not exist" << std::endl;
        return 0;
    }

    std::vector <Point> point_data;
    int count = 0;
    if (fin.is_open()) {
        double xx, yy, zz;
        while (fin >> xx >> yy >> zz) {
#ifndef SCALE
            point_data.emplace_back(xx, yy, zz, 1 << 30, count);
#else
	    point_data.emplace_back(xx / 100.0, yy / 100.0, zz / 100.0, 1 << 30, count);
#endif
            count++;
        }
    }
    fin.close();
    const int pointSize = point_data.size();
    //copy to array
    auto points = (Point*)malloc(pointSize * sizeof(Point));
    for(int i = 0; i < pointSize;i++){
        points[i] = point_data[i];
    }

    auto samplePoints = (Point*) malloc(sample_number*sizeof(Point));
#ifdef METRICS
    printf("Total:%d\n", pointSize);
#endif

    clock_t start_t, end_t;
    clock_t start_build_t, end_build_t;
    // 建立KD树
    Point init_point = points[0];
    start_t = clock();
    samplePoints[0] = init_point;

    //auto test = (KDNode*)malloc(pointSize * sizeof(KDNode));


#ifdef LINE
    KDLineTree tree = KDLineTree(points,pointSize,kd_height,samplePoints);
#else
    KDTree tree = KDTree(points,pointSize,samplePoints);
#endif
    start_build_t = clock();
    tree.buildKDtree();
    end_build_t = clock();
    tree.init(init_point);
    tree.sample(sample_number);

    end_t = clock();
#ifndef METRICS
    std::cout << "Report:" << std::endl;
#ifdef LINE
    std::cout << "    Type   :KDLineTree  " << "High:" << kd_height << std::endl;
#else
    std::cout << "    Type   :KDTree" << std::endl;

#endif
    std::cout << "    Points :" << pointSize << std::endl;
    std::cout << "    NPoint :" << sample_number << std::endl;
    std::cout << "    RunTime:" << (double) (end_t - start_t) << "us" << std::endl;
    std::cout << "    Build  :" << (double) (end_build_t - start_build_t) << "us" << std::endl;
    std::cout << "    MM(%)  : " << tree.memory_ops * 100.0 / (point_data.size() * sample_number) << "%"
              << std::endl;
    std::cout << "    OP(%)  : " << tree.mult_ops * 100.0 / (point_data.size() * sample_number) << "%" << std::endl;
    std::cout << "    Check  :" << tree.verify(sample_number) << std::endl;
    std::cout << "    Param  :" << filename << std::endl;
    std::time_t result = std::time(nullptr);
    std::cout << "  Timestamp:" << std::asctime(std::localtime(&result)) << std::endl;

#endif
    free(samplePoints);
    free(points);
    //free(test);
    return 0;
}
