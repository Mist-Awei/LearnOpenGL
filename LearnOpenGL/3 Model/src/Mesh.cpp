#include "Mesh.h"

#include <string>

Mesh::Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, const std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
    
	setupMesh();
}

void Mesh::Draw(Shader shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        // 激活并绑定相应的纹理单元
        textures[i].Bind(i);
        // 获取纹理序号（diffuse_textureN 中的 N）
        std::string number;
        std::string name = textures[i].GetType();
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string
        // 为采样器设置正确的纹理单元
        shader.setInt(("material." + name + number).c_str(), i);
    }

    // 绘制网格
    VAO.Bind();
    // GLCall(glBindVertexArray(VAO));
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    //VAO.Unbind();

    // 解绑纹理
    GLCall(glActiveTexture(GL_TEXTURE0));
}

void Mesh::Delete()
{
    VBO.Delete();
    VAO.Delete();
    EBO.Delete();

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        // 释放相应的纹理单元
        textures[i].Delete();
    }
}

void Mesh::setupMesh()
{
    VBO.AddBuffer(vertices);
    EBO.AddBuffer(indices);

    VertexBufferLayout layout;
    layout.Push<float>(3); // 顶点位置
    layout.Push<float>(3); // 顶点法线
    layout.Push<float>(2); // 顶点纹理坐标
    layout.Push<float>(3); // 顶点切线
    layout.Push<float>(3); // 顶点副切线
    layout.Push<int>(4); // 骨骼ids
    layout.Push<float>(4); // 权重

	VAO.AddBuffer(VBO, layout);
    VAO.Unbind();
}