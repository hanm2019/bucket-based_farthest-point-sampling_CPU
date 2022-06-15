objects= src/Interval.cpp src/Interval.h src/KDNode.cpp src/KDNode.h src/KDLineTree.cpp src/KDLineTree.h src/KDTree.cpp src/KDTree.h src/KDTreeBase.cpp src/KDTreeBase.h src/Point.cpp src/Point.h
build:
	mkdir -p build && cd build && cmake .. && make

O3:
	g++ ${objects} src/kdtree_main.cpp -DLINE -O3 -o kdline
