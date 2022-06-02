#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

const float PI = 3.14159265359f;


class Cube
{
private:
    friend class RCube;

    static const float positions[70];
    static const unsigned int indices[36];

    VertexArray m_va;
    VertexBuffer m_vb;
    VertexBufferLayout m_layout;
    IndexBuffer m_ib;

    Texture m_texture;
    Shader  m_shader;

public:
    Cube(const std::string& _FilePath = "DefaultTexture.png");

    const VertexArray& GetVerArr() const { return m_va; };
    const IndexBuffer& GetIndBuf() const { return m_ib; };
    Shader& GetShader() { return m_shader; };
    const Texture& GetTexture() const { return m_texture; };

    

    void Unbind() const;
    void Bind() const;
};
