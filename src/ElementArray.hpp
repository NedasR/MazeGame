#pragma once

class ElementArray
{
	private:
	unsigned int m_rendererID;
	unsigned int m_count;

	public:
		ElementArray(const unsigned int* data,const unsigned int count);

		ElementArray();

		~ElementArray();

		void createElementArray(const unsigned int* data, const unsigned int count);

		void Bind() const;

		void Unbind() const;

		inline unsigned int getCount() {return m_count;}

		inline unsigned int& getID(){return m_rendererID;}
};