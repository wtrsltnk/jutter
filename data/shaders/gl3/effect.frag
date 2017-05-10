#version 150

uniform sampler2D tex;
uniform vec4 u_color;

in vec2 f_uv;
in vec4 f_color;
out vec4 fragColor;

void main()
{
   fragColor = f_color * u_color * texture2D(tex, f_uv.st);
}
