#pragma once
#include <vector>
#include <glew.h>
#include <stdexcept>

struct VertexBufferElements
{
public:
	unsigned int m_count;
	bool m_normalized;
	int m_type;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		//add more types later
		}
		return 0;
	}
};

class VertexBufferLayout
{
private:
	unsigned int m_stride;
	std::vector<VertexBufferElements> m_elements;
public:

	VertexBufferLayout();

	inline unsigned int getStride(){return m_stride;}
	inline const std::vector<VertexBufferElements> getElements() const& {return m_elements;}

	template<typename T>
	void Push(unsigned int count, bool normalized)
	{
		std::runtime_error;
	}

	template<>
	void Push<float>(unsigned int count,bool normalized)
	{
		m_elements.push_back({ count , normalized, GL_FLOAT});
		m_stride += sizeof(float) * count;
	}

};