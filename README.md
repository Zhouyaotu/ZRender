# ZRender 软光栅化渲染器
A Software Renderer

## 开发路线
### Step 1
    类：Rasterizer(支持顶点数据、着色器输入)
        |-包含各种缓冲区
    类：Mesh(三角形)：将顶点数据组装成mesh 
    功能：Vertex Shader(MVP)
    功能：透视除法与视口变换
    功能：绘制直线和点
    功能：遍历mesh外接矩形
    功能：判断像素在三角形内
    功能：重心坐标插值
    功能：Fragment Shader(直接输出color)
    功能：draw函数绘制mesh

### Step 2
    类：Model(加载模型)
    类：Texture(纹理)
    功能：深度测试
    功能：裁剪
    功能：背面剔除
    功能：FragmentShader(纹理映射)

## 依赖
    操作系统：Ubuntu
    数学库：Eigen
    模型导入库：Assimp
    图像库：stbi_image



