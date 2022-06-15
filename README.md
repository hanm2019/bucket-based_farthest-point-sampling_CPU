# KD-Tree based Farthest point sampling for largest-sacled point clouds

we use an approximate KD-Tree to devide the point clouds into multi-buckets and use two geometry inequality to reduce the distance computation times and the data which need to load from memory

we achieve  `42ms` on CPU for a 50k points (sample 4K point subset)

# USAGE

```
make build
./main kdtree_high num_sample_point 
```


# Cite
Please kindly consider citing this repo in your publications if it helps your research.

```
@misc{KD-Tree-Based-Farthest-point-sampling,
    title={KD-Tree Based Farthest point sampling},
    author={Limin Xiao, Liang Wang, Meng Han},
    howpublished = {\url{https://github.com/hanm2019/KD-Tree-Based-Farthest-point-sampling}},
    year={2021}
}
```

# TODO
we will write this to CUDA to enable running more faster and offer an API for PointNet++ based point cloud learning speed up

in addition, We have designing an accelerator to achieve FPS use only `1ms` to  down-sampling an 60K pointcloud to 4K 
