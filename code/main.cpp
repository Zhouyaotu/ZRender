#include "global.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Rasterizer.hpp"

#include <cstdio>
#include <iostream>

float vertices[] = {
    // ---- 位置 ----  ---- 颜色 ----    - 纹理坐标 -
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // 左上
};

unsigned int indices[] = {
    // 注意索引从0开始!
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

int main(int argc, char** argv)
{
    int w, h, n;

    //rgba
    //load image
    unsigned char *data = stbi_load("../asset/img/container.jpg", &w, &h, &n, 0);

    //change pixel
    //rgba,write 10 red pixel at line 11
    for (int dx = 0; dx < 10; ++dx)
    {
        data[n * w * 10 + dx * n + 0] = 255;
        data[n * w * 10 + dx * n + 1] = 0;
        data[n * w * 10 + dx * n + 2] = 0;
        data[n * w * 10 + dx * n + 3] = 255;
    }
    stbi_write_png("write.png", w, h, n, data, w * n);

    stbi_image_free(data);

    // assimp
    Model mod1 = Model("../asset/model/marry/Marry.obj");

    // mesh
    std::vector<Vertex> vert;
    std::vector<unsigned int> ind(indices, indices+6);
    for(int i=0; i<4; i++)// 4 verts
    {
        Vertex aVert;
        aVert.Position = Eigen::Vector3f(vertices[i * 8], vertices[i*8 + 1], vertices[i*8 + 2]);
        aVert.TexCoords = Eigen::Vector2f(vertices[i*8 + 6], vertices[i*8 + 7], vertices[i*8 + 8]);
        vert.push_back(aVert);
    }
    Mesh twoTri = Mesh(vert, ind);

    return 0;
}