#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform float gamma;
uniform bool isGamma;

void main()
{    
    vec4 color = texture(skybox, TexCoords);

    if(isGamma)
        color.rgb = pow(color.rgb, vec3(1.0/gamma));

    FragColor = color;
}