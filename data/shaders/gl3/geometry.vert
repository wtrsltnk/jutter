#version 150

in vec3 vertex;
in vec3 normal;
in vec3 color;

uniform mat4 u_p;
uniform mat4 u_v;
uniform mat4 u_m;

out vec4 f_color;

void main()
{
    // Position
    gl_Position = u_p * u_v * u_m * vec4(vertex.xyz, 1.0);

    // Color
    f_color = vec4(color.xyz, 1.0);
}
