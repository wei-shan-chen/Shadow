#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
	vec3 Normal;
    vec3 Color;
	vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;


uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool shader;
uniform sampler2D texturemap;
uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float bias = max(0.0002 * (1.0 - dot(normal, lightDir))/2.0, 0.0001);
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}


// function prototypes
void main()
{
    // ka,kd,ks   ia,id,is
    float ka = 0.3, kd = 0.8, ks = 0.5;
    vec3 Ia = vec3(0.3, 0.3, 0.3);
    vec3 Id = vec3(0.8, 0.8, 0.8);
    vec3 Is = vec3(0.8, 0.8, 0.8);

    // ambient
    vec3 ambient = ka * Ia;
    // diffuse
    vec3 L = normalize(lightPos - fs_in.FragPos);
    vec3 N = normalize(fs_in.Normal);
    vec3 diffuse = kd * Id * max(dot(L, N), 0.0);
    // specular
    vec3 V = normalize(viewPos - fs_in.FragPos);
    vec3 R = reflect(-1*L, N);     
    vec3 specular = ks * Is * pow(max(dot(V, R), 0.0), 256.0); 

    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);

    if(shader){ 
        vec3 I = vec3(ambient + (1.0 - shadow) * (diffuse + specular))*fs_in.Color.rgb;
        FragColor = vec4(I, 1.0);
    }else{
        vec3 texcolor = texture(texturemap, fs_in.TexCoords).rgb;
        vec3 I = vec3(ambient + (1.0 - shadow) * (diffuse + specular))*texcolor;
        FragColor = vec4(I, 1.0);
    }
    
} 
