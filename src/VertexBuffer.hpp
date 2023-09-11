#pragma once

class VertexBuffer
{
	private:
	unsigned int m_rendererID;

	public:
	VertexBuffer(const void* data,const int size);

	VertexBuffer();

	~VertexBuffer();

	void createVertexBuffer(const void* data, const int size);
	void bind() const;
	void unbind() const;
	inline unsigned int& getID(){return m_rendererID;}
};