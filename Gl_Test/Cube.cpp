#include "Cube.h"


const float Cube::positions[70] =
{
	//	 Vertex Position			Texture Position
		-50.0f,  50.0f, -50.0f,		0.25f,  1.0f,   //0
		 50.0f,  50.0f, -50.0f,		0.5f,   1.0f,	//1
		 50.0f,  50.0f,  50.0f,		0.5f,  0.75f,	//2
		-50.0f,  50.0f,  50.0f,		0.25f, 0.75f,	//3

		-50.0f,  50.0f, -50.0f,		0.0f,  0.75f,   //4
	// 	-50.0f,  50.0f,  50.0f,		0.25f, 0.75f,	//3
		-50.0f, -50.0f,  50.0f,		0.25f,  0.5f,   //5
		-50.0f, -50.0f, -50.0f,		0.0f,   0.5f,	//6

	//	-50.0f,  50.0f,  50.0f,		0.25f, 0.75f,   //3   
	//	 50.0f,  50.0f,  50.0f,		0.5f,  0.75f,   //2
		 50.0f, -50.0f,  50.0f,		0.5f,   0.5f,   //7
	//	-50.0f, -50.0f,  50.0f,		0.25f,  0.5f,   //5

	//	 50.0f,  50.0f,  50.0f,		0.5f,  0.75f,  //2
		 50.0f,  50.0f, -50.0f,		0.75f, 0.75f,  //8
		 50.0f, -50.0f, -50.0f,		0.75f,  0.5f,  //9
	//	 50.0f, -50.0f,  50.0f,		0.5f,   0.5f,  //7

	//	-50.0f, -50.0f,  50.0f,		0.25f,  0.5f,  //5 
	//	 50.0f, -50.0f,  50.0f,		0.5f,   0.5f,  //7
		 50.0f, -50.0f, -50.0f,		0.5f,  0.25f,  //10
		-50.0f, -50.0f, -50.0f,		0.25f, 0.25f,  //11

	//	-50.0f, -50.0f, -50.0f,		0.25f, 0.25f,  //11
	//	 50.0f, -50.0f, -50.0f,		0.5f,  0.25f,  //10
		 50.0f,  50.0f, -50.0f,		0.5f,   0.0f,  //12
		-50.0f,  50.0f, -50.0f,		0.25f,  0.0f   //13
};

const unsigned int Cube::indices[36] =
{
	0, 1, 2,
	2, 3, 0,

	4, 3, 5,
	5, 6, 4,

	3, 2, 7,
	7, 5, 3,

	2, 8, 9,
	9, 7, 2,

	5,  7,  10,
	10, 11, 5,

	11, 10, 12,
	12, 13, 11
};


Cube::Cube(const std::string& _FilePath)
	:
	m_va(),
	m_ib(indices, 36),
	m_vb(positions, 14 * 5 * sizeof(float)),
	m_layout(),
	m_shader(),
	m_texture(_FilePath)
{
	m_layout.Push <float>(3);
	m_layout.Push <float>(2);
	m_va.AddBuffer(m_vb, m_layout);

	Unbind();
}

void Cube::Unbind() const
{
	m_va.Unbind();
	m_vb.Unbind();
	m_ib.Unbind();
	m_texture.Unbind();
	m_shader.Unbind();
}

void Cube::Bind() const
{
	m_shader.Bind();
	m_va.Bind();
	m_texture.Bind();
	m_ib.Bind();
}