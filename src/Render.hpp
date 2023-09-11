#pragma once
#include <glew.h>

void GlClearError();

bool GLPrintError(const char* function, int line, const char* filepath);

#define BREAK(x) if(x) __debugbreak();

#define GLCALL(x) GlClearError();\
x;\
BREAK(GLPrintError(#x,__LINE__,__FILE__))

class VertexArray;
class ElementArray;
class Shader;



class Renderer
{
public:

	void draw(VertexArray& vertexArray, ElementArray& indexBuffer,Shader& shader);
	void drawArrays(VertexArray& vertexArray, Shader& shader);
};
