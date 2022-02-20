#include "global.hpp"
#include "Rasterizer.hpp"
#include <iostream>

static std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Eigen::Vector4f* v){
    float c1 = (x*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*y + v[1].x()*v[2].y() - v[2].x()*v[1].y()) / (v[0].x()*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*v[0].y() + v[1].x()*v[2].y() - v[2].x()*v[1].y());
    float c2 = (x*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*y + v[2].x()*v[0].y() - v[0].x()*v[2].y()) / (v[1].x()*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*v[1].y() + v[2].x()*v[0].y() - v[0].x()*v[2].y());
    float c3 = (x*(v[0].y() - v[1].y()) + (v[1].x() - v[0].x())*y + v[0].x()*v[1].y() - v[1].x()*v[0].y()) / (v[2].x()*(v[0].y() - v[1].y()) + (v[1].x() - v[0].x())*v[2].y() + v[0].x()*v[1].y() - v[1].x()*v[0].y());
    return {c1,c2,c3};
}

static bool insideTriangle(int x, int y, const Eigen::Vector4f* _v){
    Eigen::Vector3f v[3];
    for(int i=0;i<3;i++)
        v[i] = {_v[i].x(), _v[i].y(), 1.0};
    Eigen::Vector3f f0,f1,f2;
    f0 = v[1].cross(v[0]);
    f1 = v[2].cross(v[1]);
    f2 = v[0].cross(v[2]);
    Eigen::Vector3f p(x,y,1.);
    if((p.dot(f0)*f0.dot(v[2])>0) && (p.dot(f1)*f1.dot(v[0])>0) && (p.dot(f2)*f2.dot(v[1])>0))
        return true;
    return false;
}

Rasterizer::Rasterizer(int w, int h): width(w), height(h)
{   
    frame_buf.resize(w * h);
    depth_buf.resize(w * h);
}

int Rasterizer::get_index(int x, int y)
{
    return (height - y) * width + x;
}

void Rasterizer::set_pixel(int x, int y, Eigen::Vector3f color)
{
    int idx = get_index(x, y);
    if(idx >=0 && idx < width*height)
        frame_buf[idx] = color;
    else
        std::cout<<" buffer index error!"<<std::endl;
    return ;
}

