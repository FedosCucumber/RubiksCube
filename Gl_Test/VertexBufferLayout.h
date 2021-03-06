#pragma once
#include "Renderer.h"
#include <vector>



struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:		   return 4;
		case GL_UNSIGNED_INT:  return 4;
		case GL_UNSIGNED_BYTE: return 1;
		default: break;
		}
		_ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector <VertexBufferElement> m_Elements;
	unsigned int m_Stride = 0;
public:

	VertexBufferLayout() = default;

	template <typename T>
	void Push (unsigned int count)
	{
		_ASSERT(false);
	}

	template <>
	void Push <float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template <>
	void Push <unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);

	}

	template <>
	void Push <unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	std::vector <VertexBufferElement> const& GetElements() const { return m_Elements; }
	unsigned int GetStride() const { return m_Stride; }

};