#version 100

attribute vec3 vertex;
attribute vec3 normal;
attribute vec3 uv;

uniform mat4 u_p;
uniform mat4 u_v;
uniform mat4 u_m;

varying vec2 f_uv;
varying vec4 f_color;

void main()
{
    // Position
    gl_Position = u_p * u_v * u_m * vec4(vertex.xyz, 1.0);

    // Texcoords
    f_uv = uv.xy;

    // Light color
    f_color = vec4(1.0, 1.0, 1.0, 1.0);
}
