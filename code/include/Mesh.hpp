#ifndef MESH_H
#define MESH_H

#include"global.hpp"

struct Vertex
{
    /* data */
    Eigen::Vector3f Position;
    Eigen::Vector3f Normal;
    Eigen::Vector2f TexCoords;
};


class Mesh
{
private:
    /* data */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Eigen::Vector3f ka,kd,ks;

public:
    Mesh(/* args */);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
             Eigen::Vector3f ka, Eigen::Vector3f kd, Eigen::Vector3f ks);
    ~Mesh();
};

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, 
             Eigen::Vector3f ka, Eigen::Vector3f kd, Eigen::Vector3f ks)
{
    this->vertices = vertices;
    this->indices = indices;

    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
}

Mesh::~Mesh()
{
}


#endif