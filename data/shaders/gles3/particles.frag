#version 100
precision mediump float;

uniform sampler2D u_tex;
uniform vec4 u_global_color;

varying vec2 v_texcoord;

void main()
{
    vec4 t = texture2D(u_tex, v_texcoord.st);
    gl_FragColor = vec4(u_global_color.xyz, t.a * u_global_color.w);
}
