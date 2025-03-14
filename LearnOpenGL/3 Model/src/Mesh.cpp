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
        // �������Ӧ������Ԫ
        textures[i].Bind(i);
        // ��ȡ������ţ�diffuse_textureN �е� N��
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
        // Ϊ������������ȷ������Ԫ
        shader.setInt(("material." + name + number).c_str(), i);
    }

    // ��������
    VAO.Bind();
    // GLCall(glBindVertexArray(VAO));
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    //VAO.Unbind();

    // �������
    GLCall(glActiveTexture(GL_TEXTURE0));
}

void Mesh::Delete()
{
    VBO.Delete();
    VAO.Delete();
    EBO.Delete();

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        // �ͷ���Ӧ������Ԫ
        textures[i].Delete();
    }
}

void Mesh::setupMesh()
{
    VBO.AddBuffer(vertices);
    EBO.AddBuffer(indices);

    VertexBufferLayout layout;
    layout.Push<float>(3); // ����λ��
    layout.Push<float>(3); // ���㷨��
    layout.Push<float>(2); // ������������
    layout.Push<float>(3); // ��������
    layout.Push<float>(3); // ���㸱����
    layout.Push<int>(4); // ����ids
    layout.Push<float>(4); // Ȩ��

	VAO.AddBuffer(VBO, layout);
    VAO.Unbind();
}