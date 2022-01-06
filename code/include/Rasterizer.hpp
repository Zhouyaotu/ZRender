#ifndef RASTERIZER_H
#define RASTERIZER_H

#include"global.hpp"
#include<vector>

class Rasterizer
{
private:
    int width, height;
    std::vector<Eigen::Vector3f> frame_buf;
    std::vector<float> depth_buf;
    int get_index(int x, int y);

public:
    Rasterizer();

};

#endif