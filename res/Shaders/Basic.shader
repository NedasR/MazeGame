#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
//layout(location = 1) in vec3 acolor;
layout(location = 1) in vec2 texCordsin;

//out vec3 setcolor;
out vec2 texCords;

uniform mat4 model;
uniform mat4 prespective;
uniform mat4 view;

void main()
{
    gl_Position = prespective * view * model * position;
    //setcolor = acolor;
    texCords = texCordsin;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//in vec3 setcolor;
in vec2 texCords;

uniform vec3 CsetColor;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
  //color = texture(ourTexture1, texCords) * vec4(CsetColor, 1.0);
  color = mix(texture(ourTexture1,texCords), texture(ourTexture2, texCords),0.5) * vec4(CsetColor, 1.0);

};