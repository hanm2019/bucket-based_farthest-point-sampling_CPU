# Bucket-based Farthest point sampling for largest-scaled point clouds 

![](https://komarev.com/ghpvc/?username=hanm2019bfpsCPU)

we use an approximate KD-Tree to divide the point clouds into multi-buckets and use two geometry inequality to reduce the distance computation times and the data which need to load from memory

we achieve  `42ms` on CPU for 50k points (generate 4K sample points )

we present the CPU implementation and [GPU implementation](https://github.com/hanm2019/FPS_GPU) of bucket-based farthest point sampling.

# Importance
There is a [better repo](https://github.com/leonardodalinky/fpsample) for implementing bucket-based_farthest point sampling on the single-thread CPU. 

# BUILD

```
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

```

 then, three executable files are generated:

* baseline: the conventional implementation of  FPS, used for performance baseline.

* kdline: bucket-based farthest point sampling, each bucket contains multiple points.  **high performance** 

*  kdtree: bucket-based farthest point sampling, each bucket contains one point. 

  

# USAGE

```
./baseline  num_sample_point filename
./kdtree num_sample_point filename
./kdlinetree tree_high num_sample_point filename
```

# Cite

Please kindly consider citing this repo in your publications if it helps your research.

```
@article{han2023quickfps,
  title={QuickFPS: Architecture and Algorithm Co-Design for Farthest Point Sampling in Large-Scale Point Clouds},
  author={Han, Meng and Wang, Liang and Xiao, Limin and Zhang, Hao and Zhang, Chenhao and Xu, Xiangrong and Zhu, Jianfeng},
  journal={IEEE Transactions on Computer-Aided Design of Integrated Circuits and Systems},
  year={2023},
  publisher={IEEE}
}

@inproceedings{han2023fusefps,
  title={FuseFPS: Accelerating Farthest Point Sampling with Fusing KD-tree Construction for Point Clouds},
  author={Han, Meng and Wang, Liang and Xiao, Limin and Zhang, Hao and Zhang, Chenhao and Xie, Xilong and Zheng, Shuai and Dong, Jin},
  booktitle={2024 29th Asia and South Pacific Design Automation Conference (ASP-DAC)},
  year={2024},
  organization={IEEE}
}
```

# Resources
1. [the GPU implementation of FPS](https://github.com/hanm2019/FPS_GPU)
2. the reference paper: [QuickFPS: Architecture and Algorithm Co-Design for Farthest Point Sampling in Large-Scale Point Clouds](https://ieeexplore.ieee.org/abstract/document/10122654)
