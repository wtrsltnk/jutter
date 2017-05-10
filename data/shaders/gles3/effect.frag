#version 100
precision mediump float;

uniform sampler2D tex;
uniform vec4 u_color;

varying vec2 f_uv;
varying vec4 f_color;

void main()
{
    gl_FragColor = u_color * f_color * texture2D(tex, f_uv.st);
}
