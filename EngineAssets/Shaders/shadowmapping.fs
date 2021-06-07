#version 330 core

struct Material{
    
    sampler2D albedoMap;
};

uniform Material material;

in vec2 TexCoords;
in vec3 FragPos;  

void main()
{ 
    if(texture(material.albedoMap, TexCoords).a < 0.8)
        discard;

    gl_FragDepth = gl_FragCoord.z;
}