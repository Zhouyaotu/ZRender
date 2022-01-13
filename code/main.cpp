#include "global.hpp"
#include "Mesh.hpp"
#include "Model.hpp"

#include <cstdio>
#include <iostream>

int main(int argc, char** argv)
{
    int w, h, n;

    //rgba
    //load image
    unsigned char *data = stbi_load("../asset/img/container.jpg", &w, &h, &n, 0);

    printf("%d, %d, %d\n", w, h, n);

    //change pixel
    //rgba,write 10 red pixel at line 11
    for (int dx = 0; dx < 10; ++dx)
    {
        data[n * w * 10 + dx * n + 0] = 255;
        data[n * w * 10 + dx * n + 1] = 0;
        data[n * w * 10 + dx * n + 2] = 0;
        data[n * w * 10 + dx * n + 3] = 255;
    }

    printf("ok\n");
    //write image
    stbi_write_png("write.png", w, h, n, data, w * n);

    stbi_image_free(data);

    // assimp
    Model mod1 = Model("../asset/model/marry/Marry.obj");

    return 0;
}