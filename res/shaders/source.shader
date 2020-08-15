#shader vertex
#version 330 core
layout (location=0) in vec3 position;
layout (location=1) in vec3 color;
out vec3 v_color;
void main()
{
    v_color = color;
    gl_Position = vec4(position, 1.f);
}


#shader fragment
#version 330 core
out vec4 fragColor;
in vec3 v_color;
uniform float u_color;
void main()
{
    fragColor = vec4(vec3(.9f, u_color, .2f), 1.f);
}