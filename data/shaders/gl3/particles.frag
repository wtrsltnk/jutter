#version 140


uniform sampler2D u_tex;
uniform vec4 u_global_color;

in vec2 v_texcoord;

out vec4 fragColor;

void main()
{
    vec4 t = texture2D(u_tex, v_texcoord.st);
    fragColor = vec4(u_global_color.xyz, t.a * u_global_color.w);
}
