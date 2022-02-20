#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "global.hpp"
#include "Mesh.hpp"
#include <vector>

class Rasterizer
{
private:
    int width, height;
    std::vector<Eigen::Vector3f> frame_buf;
    std::vector<float> depth_buf;

    int get_index(int x, int y);
    void set_pixel(int x, int y, Eigen::Vector3f color);
    void draw_line(Eigen::Vector3f begin, Eigen::Vector3f end);
    bool draw_primitive();

public:
    Rasterizer(int w, int h);
    void draw(Mesh mesh);
};

#endif