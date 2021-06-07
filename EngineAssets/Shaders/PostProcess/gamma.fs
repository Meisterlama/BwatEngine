#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float gamma = 2.2;

void main()
{
    vec4 color = texture(screenTexture, TexCoords);
    
    vec3 result = pow(color.rgb, vec3(1.0 / gamma));
    
    FragColor = vec4(result, 1.0);
}
