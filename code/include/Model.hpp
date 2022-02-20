#ifndef MODEL_H
#define MODEL_H

#include "global.hpp"
#include "Mesh.hpp"
#include <iostream>
#include <string>
#include <vector>

class Model 
{
    public:
        /*  函数   */
        Model(const char *path)
        {
            loadModel(path);
        }

    private:
        /*  模型数据  */
        //std::vector<Texture2D> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;
        
        /*  函数   */
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        void loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, 
            Eigen::Vector3f &ka, Eigen::Vector3f &kd, Eigen::Vector3f &ks);
};

#endif 