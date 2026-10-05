#version 330 core

out vec4 FragColor;



 

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;

};


struct DirLight {
    vec3 direction;

    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct PointLight {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant; // BTW 1.0 
    float linear; 
    float quadratic; 
};

struct SpotLight {
    vec3 direction;
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutoff;
    float outercutoff;
    float constant; // BTW 1.0 
    float linear; 
    float quadratic; 
};


    in vec2 TexCoords;
    in vec3 Normal;
    in vec3 FragPos;
uniform Material material;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform vec3 lightPos; 
uniform vec3 viewPos; 


vec3 CalDirLight(DirLight light , vec3 Normal , vec3 viewDir);
vec3 CalPointLight(PointLight light , vec3 Normal , vec3 viewDir , vec3 FragPos);
vec3 CalSpotLight(SpotLight light , vec3 Normal , vec3 viewDir , vec3 FragPos);

void main()
{




    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos); // how to side of the cube look on the camera
    vec3 result = CalDirLight(dirLight , norm ,  viewDir);
    for(int i = 0; i < NR_POINT_LIGHTS;  i++){

       result +=  CalPointLight(pointLights[i], norm , viewDir , FragPos);
    }

   result += CalSpotLight(spotLight, norm ,  viewDir , FragPos);

    FragColor = vec4(result, 1.0);
    // mix(texture(TEXTURE1 ,Tex) , texture(TEXTURE2 , Tex) ,0.2)
} 


vec3 CalDirLight(DirLight light , vec3 Normal , vec3 viewDir){
    // DirLight calculate
    vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(Normal,lightDir),0.0);
    vec3 reflectDir = reflect(-lightDir , Normal);
    float spec = pow(max(dot(viewDir , reflectDir),0.0),material.shininess);
    

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse* diff * vec3(texture(material.diffuse , TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular , TexCoords));

    

    return (ambient + diffuse + specular); 
}

vec3 CalPointLight(PointLight light , vec3 Normal , vec3 viewDir , vec3 FragPos){
    vec3 lightDir = normalize(light.position - FragPos); 
    float diff = max(dot(Normal,lightDir),0.0);
    vec3 reflectDir = reflect(-lightDir , Normal);
    float spec = pow(max(dot(viewDir , reflectDir),0.0),material.shininess);
    
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance *distance));



    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse* diff * vec3(texture(material.diffuse , TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular , TexCoords));


    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;


    return (ambient + diffuse + specular);
}


vec3 CalSpotLight(SpotLight light , vec3 Normal , vec3 viewDir , vec3 FragPos){
    vec3 lightDir = normalize(light.position - FragPos); 
    float diff = max(dot(Normal,lightDir),0.0);
    vec3 reflectDir = reflect(-lightDir , Normal);
    float spec = pow(max(dot(viewDir , reflectDir),0.0),material.shininess);
    



    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse* diff * vec3(texture(material.diffuse , TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular , TexCoords));


    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutoff - light.outercutoff); // outcutoff all the dark 
    float intensity = clamp((theta - light.outercutoff) /  epsilon  , 0.0 , 1.0); // the light power!

    diffuse *= intensity;
    specular *= intensity;

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance *distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;



    return (ambient + diffuse + specular);

}









