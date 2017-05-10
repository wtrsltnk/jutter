#version 100
precision mediump float;

attribute vec3 a_vertex;
attribute vec2 a_texcoord;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform float u_sprite_size;

varying vec2 v_texcoord;

void main()
{
    mat4 viewmodel = u_view * u_model;

    vec2 spriteSize = vec2(u_sprite_size);
    vec4 eyePos = viewmodel * vec4(a_vertex.xyz, 1.0);
    eyePos.xy += spriteSize * (a_texcoord - vec2(0.5));
    gl_Position = u_projection * eyePos;

    v_texcoord = a_texcoord.st;
}
