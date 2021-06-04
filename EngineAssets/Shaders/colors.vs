#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in ivec4 boneIds; 
layout (location = 4) in vec4 weights;

out vec3 FragPos; 
out vec3 Normal;
out vec2 TexCoords;
out vec4 FragPosLightSpace;
out vec4 boneColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 lightSpaceMatrix;

uniform bool skinned;

uniform vec2 tile;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];


void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	
	Normal = mat3(transpose(inverse(model))) * aNormal;
	
	TexCoords =  aTexCoord * tile;
	

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
    	    vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * aNormal;
    	}

		
		gl_Position = proj * view * model * totalPosition;
		FragPos = vec3(model * totalPosition);
	}
	else
	{
		gl_Position = proj * view * vec4(FragPos, 1.0);
	}

	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
}