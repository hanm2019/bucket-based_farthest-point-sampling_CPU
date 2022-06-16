#include<cstdio>
#include<iostream>
#include<fstream>
#include<vector>
#include "Point.h"
#include "KDTreeBase.h"
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
            point_data.emplace_back(xx, yy, zz, 10000000, count);
            count++;
        }
    }
    fin.close();

    clock_t start_t, end_t;
    clock_t start_build_t, end_build_t;
    // 建立KD树
    Point init_point = point_data[0];
    start_t = clock();
#ifdef LINE
    KDLineTree tree = KDLineTree(point_data,kd_height);
#else
    KDTree tree = KDTree(point_data);
#endif
    start_build_t = clock();
    tree.buildKDtree();
    end_build_t = clock();
    tree.init(init_point);
    tree.sample(sample_number);

    end_t = clock();
    std::cout << "Report:" << std::endl;
#ifdef LINE
    std::cout << "    Type  :KDLineTree  " << "High:" << kd_height << std::endl;
    int sum = 0;
    for(auto node :tree.KDNode_list){
        sum += node->points->size();
    }
    std::cout << "KDNodes sum:" << sum << std::endl;

#else
    std::cout << "    Type  :KDTree" << std::endl;

#endif
    std::cout << "root sum:" << tree.root_->size()<< std::endl;
    std::cout << "    Points:" << point_data.size() << std::endl;
    std::cout << "    NPoint:" << sample_number << std::endl;
    std::cout << "    Time  :" << (double) (end_t - start_t) << "us" << std::endl;
    std::cout << "Build Time  :" << (double) (end_build_t - start_build_t) << "us" << std::endl;
    std::cout << "    memory load rate: " << tree.memory_ops * 100.0 / (point_data.size() * sample_number) << "%"
              << std::endl;
    std::cout << "    mult rate: " << tree.mult_ops * 100.0 / (point_data.size() * sample_number) << "%" << std::endl;
    std::cout << "id sum:" << tree.verify() << std::endl;

    return 0;
}
