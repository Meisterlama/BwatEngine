#version 330 core
out vec4 FragColor;

struct Material {

    sampler2D normal;
    sampler2D albedoMap;
    sampler2D metallicMap;
    sampler2D roughnessMap;
    sampler2D aoMap;

    bool isTextured;
    bool isNormal;
    
    vec3  albedo;
    float metallic;
    float roughness;
    float ao;
}; 

struct Light {

    vec3 position;
    vec3 direction;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float intensity;

    // SpotLight
    float cutOff;
    float outerCutOff;
	
    //Point Light
    float constant;
    float linear;
    float quadratic;

    int typeoflight;
};


// === from Color.vs 

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec4 FragPosLightSpace;

// General Values

uniform vec3 viewPos;
uniform Light light[20];
uniform Material material;

uniform int nbrlights;
uniform sampler2D shadowMap;
uniform samplerCube envMap;

// === material values

vec3 albedoG;
float metallicG;
float roughnessG ;
float aoG;

uniform float envMix = 0.0;

// === function prototypes

vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir, vec3 F0);
vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir,vec3 F0);
vec3 CalcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir,vec3 F0);

// === shadow 

uniform float biasValue = 0.0002;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightpos, vec3 norm);

// ==== PBR Calcul

const float PI = 3.14159265359;
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);
vec3 getNormalFromMap();

// ========================================= Main ========================================= //

void main()
{    
    
    if (texture(material.albedoMap, TexCoords).a < 0.8)
        discard;

    if(material.isTextured)
    {
        albedoG    = pow(texture(material.albedoMap, TexCoords).rgb, vec3(2.2));
        metallicG  = texture(material.metallicMap, TexCoords).r;
        roughnessG = texture(material.roughnessMap, TexCoords).r;
        aoG        = texture(material.aoMap, TexCoords).r;
    }
    else
    {
        albedoG    = material.albedo;
        metallicG  = material.metallic;
        roughnessG = material.roughness;
        aoG        = material.ao;
    }

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    if(material.isNormal)
        norm = getNormalFromMap();
    
    vec4 envcolor = texture(envMap, reflect(-viewDir, norm));

    vec3 result;
    result.x = 0;
    result.y = 0;
    result.z = 0;

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedoG, metallicG);
    
    for(int i = 0; i < nbrlights; i++)
    {
        //directional
        if(light[i].typeoflight == 0)
            result += CalcDirLight(light[i], norm, viewDir, F0);
        //point
        if(light[i].typeoflight == 1)
            result += CalcPointLight(light[i], norm, FragPos, viewDir,F0);    
        //Spot
        if(light[i].typeoflight == 2)
            result += CalcSpotLight(light[i], norm, FragPos, viewDir,F0);    
    }
    
    vec3 ambient = vec3(0.03) * albedoG * aoG;

    result = ambient + result;

    //result = result / (result + vec3(1.0));

    vec3 color = mix(result, envcolor.rgb, envMix);

    FragColor = vec4(color,texture(material.albedoMap, TexCoords).a);
}


// ========================================= Light Calcul ========================================= //


// calculates the color when using a directional light.
vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir,vec3 F0)
{
    // calculate per-light radiance
    vec3 L = normalize(-light.direction);
    vec3 H = normalize(viewDir + L);


    // Cook-Torrance BRDF
    float NDF = DistributionGGX(normal, H, roughnessG);   
    float G   = GeometrySmith(normal, viewDir, L, roughnessG);      
    vec3 F    = fresnelSchlick(max(dot(H, viewDir), 0.0), F0);
           
    vec3 nominator    = NDF * G * F; 
    float denominator = 4 * max(dot(normal, viewDir), 0.0) * max(dot(normal, L), 0.0) + 0.001; 
    vec3 specular = nominator / denominator;
        
    // kS is equal to Fresnel
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallicG;	  

    // scale light by NdotL
    float NdotL = max(dot(normal, L), 0.0);        

    // shadow 
    float shadow = ShadowCalculation(FragPosLightSpace, light.direction, normal);

    // add to outgoing radiance Lo
    return (kD * albedoG / PI + specular) * (light.diffuse * light.intensity) * NdotL * (1.0 - shadow);
}

// calculates the color when using a point light.
vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir,vec3 F0)
{
    // calculate per-light radiance
    vec3 L = normalize(light.position - fragPos);
    vec3 H = normalize(viewDir + L);

    float distance = length(light.position - viewDir);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = light.diffuse * light.intensity * attenuation;

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(normal, H, roughnessG);   
    float G   = GeometrySmith(normal, viewDir, L, roughnessG);      
    vec3 F    = fresnelSchlick(max(dot(H, viewDir), 0.0), F0);
           
    vec3 nominator    = NDF * G * F; 
    float denominator = 4 * max(dot(normal, viewDir), 0.0) * max(dot(normal, L), 0.0) + 0.001; 
    vec3 specular = nominator / denominator;
        
    // kS is equal to Fresnel
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallicG;	  

    // scale light by NdotL
    float NdotL = max(dot(normal, L), 0.0);        

    // add to outgoing radiance Lo
    return (kD * albedoG / PI + specular) * radiance  * NdotL;
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 F0)
{
    // calculate per-light radiance
    vec3 L = normalize(light.position - fragPos);
    vec3 H = normalize(viewDir + L);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    vec3 radiance = light.diffuse * attenuation;

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(normal, H, roughnessG);   
    float G   = GeometrySmith(normal, viewDir, L, roughnessG);      
    vec3 F    = fresnelSchlick(max(dot(H, viewDir), 0.0), F0);
           
    vec3 nominator    = NDF * G * F; 
    float denominator = 4 * max(dot(normal, viewDir), 0.0) * max(dot(normal, L), 0.0) + 0.001; 
    vec3 specular = nominator / denominator;
        
    // kS is equal to Fresnel
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallicG;	  

    // scale light by NdotL
    float NdotL = max(dot(normal, L), 0.0);   

    // spotlight intensity
    float theta = dot(L, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);     

    // add to outgoing radiance Lo
    return (kD * albedoG / PI + specular) * radiance  * NdotL * intensity;

}


// ========================================= Shadow ========================================= //


float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightdir, vec3 norm)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    
    vec3 normal = normalize(norm);
    vec3 lightDir = normalize(lightdir);
    float bias = biasValue * (1.0 - dot(normal, lightDir));
    
    //float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias  > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 15.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}


// ========================================= PBR ========================================= //


vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(material.normal, TexCoords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(FragPos);
    vec3 Q2  = dFdy(FragPos);
    vec2 st1 = dFdx(TexCoords);
    vec2 st2 = dFdy(TexCoords);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}
