#version 150

in vec4 f_color;
out vec4 fragColor;

void main()
{
    fragColor = f_color;
    if (f_color.r < 0.6) fragColor = vec4(163.0/255.0, 204.0/255.0, 255.0/255.0, 1.0);
    else if (f_color.r < 0.64) fragColor = vec4(250.0/255.0, 242.0/255.0, 199.0/255.0, 1.0);
    else if (f_color.r < 0.67) fragColor = vec4(240.0/255.0, 237.0/255.0, 229.0/255.0, 1.0);
    else
    {
        if (f_color.g > 0.5)
            fragColor = vec4(240.0/255.0, 237.0/255.0, 229.0/255.0, 1.0);
        else
            fragColor = vec4(210.0/255.0, 228.0/255.0, 200.0/255.0, 1.0);
    }
}
