#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCords;
layout(location = 2) in vec3 normals;

//out vec3 setcolor;
out vec3 fragnormals;

out vec2 fragTexCoords;

uniform mat4 model;
uniform mat4 prespective;
uniform mat4 view;

void main()
{
    gl_Position = prespective * view * model * vec4(position, 1.0);
    fragTexCoords = texCords;
    fragnormals = normals;
};

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 fragTexCoords;

in vec3 fragnormals;

uniform sampler2D ourTexture1;

void main()
{   
    vec4 texture1 = texture(ourTexture1, fragTexCoords);
    vec4 color = vec4(fragnormals,1.0f);
    FragColor = texture1 * vec4(0.5f, 0.5f, 0.5f, 1.0f) ;
    //* color
    //texture(ourTexture1, texCords)
};