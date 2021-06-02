#version 330 core

in vec3 FragPos;  

void main()
{ 
    gl_FragDepth = gl_FragCoord.z;
}