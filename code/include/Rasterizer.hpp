#ifndef RASTERIZER_H
#define RASTERIZER_H

#include"global.hpp"
#include"Mesh.hpp"
#include<vector>

class Rasterizer
{
private:
    int width, height;
    std::vector<Eigen::Vector3f> frame_buf;
    std::vector<float> depth_buf;

    int get_index(int x, int y);
    void draw_line(Eigen::Vector3f begin, Eigen::Vector3f end);
    bool draw_primitive();

public:
    Rasterizer(int w, int h);
    std::vector<Eigen::Vector3f> frame_buffer() { return frame_buf; }
    void draw(Mesh mesh);
};

#endif