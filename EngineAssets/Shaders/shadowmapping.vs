#version 330 core
layout (location = 0) in vec3 aPos;

layout (location = 3) in ivec4 boneIds; 
layout (location = 4) in vec4 weights;


out vec3 FragPos; 

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

uniform bool skinned;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

void main()
{
    if (skinned)
	{
		vec4 totalPosition = vec4(0.0f);
    	for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    	{
    	    if(boneIds[i] == -1) 
    	        continue;

    	    if(boneIds[i] < 0 || boneIds[i] >= MAX_BONES) 
    	        break;

    	    vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(aPos,1.0f);
    	    totalPosition += localPosition * weights[i];
    	}

		
		gl_Position = lightSpaceMatrix * model * totalPosition;

		FragPos = vec3(model * totalPosition);
	}
	else
	{
	    FragPos = vec3(model * vec4(aPos, 1.0));
    
        gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
    }
}