#include "Model.hpp"

void Model::loadModel(std::string path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));         
    }
    // 接下来对它的子节点重复这一过程
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    //std::vector<Texture2D> textures;
    //std::cout << mesh->mNumVertices;
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // 处理顶点位置、法线和纹理坐标
        Eigen::Vector3f vector; 
        
        vector.x() = mesh->mVertices[i].x;
        vector.y() = mesh->mVertices[i].y;
        vector.z() = mesh->mVertices[i].z; 
        vertex.Position = vector;

        if(mesh->HasNormals())
        {
            vector.x() = mesh->mNormals[i].x;
            vector.y() = mesh->mNormals[i].y;
            vector.z() = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        if(mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
        {
            Eigen::Vector2f vec;
            vec.x() = mesh->mTextureCoords[0][i].x; 
            vec.y() = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = Eigen::Vector2f(0.0f, 0.0f);
        vertices.push_back(vertex);
    }

    // 处理索引
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        //std::cout<<face.mNumIndices<<std::endl;
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // 处理材质
    Eigen::Vector3f ka, kd, ks;
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::cout<< "model - vert:face " <<mesh->mNumVertices << ":" << mesh->mNumFaces << std::endl;
        
        loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", ka, kd, ks);
        //textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        //loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", ka, kd, ks);
        //textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, ka, kd, ks);
}

void Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, 
    Eigen::Vector3f &ka, Eigen::Vector3f &kd, Eigen::Vector3f &ks)
{
    //std::vector<Texture2D> textures;

    for(int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str, name;
        aiColor3D color;
        
        mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
        ka = Eigen::Vector3f(color.r, color.g, color.b);
        mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        kd = Eigen::Vector3f(color.r, color.g, color.b);
        mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
        ks = Eigen::Vector3f(color.r, color.g, color.b);
        //std::cout << color.r << std::endl;

        mat->GetTexture(type, i, &str);
        //mat->Get(AI_MATKEY_TEXTURE(type, i), str);
        //std::cout << "texture" <<str.C_Str() << std::endl;
        
        //std::cout << skip << std::endl;
        // load texture
        //
    }
    return ;
}