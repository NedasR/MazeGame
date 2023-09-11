#pragma once

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray
{
	private:
	unsigned int m_renderID;

	public:
	VertexArray();
	~VertexArray();

	void makeID();

	void addBuffer(const VertexBuffer& vb, VertexBufferLayout& Layout);

	void Bind() const;

	void Unbind() const;

	inline unsigned int& getID(){return m_renderID;}

};