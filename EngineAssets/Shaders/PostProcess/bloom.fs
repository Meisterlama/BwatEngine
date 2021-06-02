#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec4 color = texture(screenTexture, TexCoords);
    vec3 highlights = clamp(color.rgb - vec3(1.0), 0.0, 1.0);
    FragColor = vec4(color.rgb + highlights * 5.0, 1.0);
} 