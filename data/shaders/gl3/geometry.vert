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

    // Light color
//    vec3 vertexPosition_cameraspace  = vec4(u_v * u_m * vec4(vertex,0)).xyz;
//    vec3 EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;
//    vec3 LightPosition_cameraspace = vec4(u_v * vec4(-500.0, 500.0, 500.0,1)).xyz;
//    vec3 LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
//    vec3 Normal_cameraspace = vec4(u_v * u_m * vec4(normal,0)).xyz;
//    vec3 n = normalize( Normal_cameraspace );
//    vec3 l = normalize( LightDirection_cameraspace );
//    float cosTheta = clamp( dot( n,l ), 0,1 );

//    f_color = (cosTheta * vec4(0.9, 0.9, 0.9, 1.0)) + vec4(0.3, 0.3, 0.3, 1.0);
}
