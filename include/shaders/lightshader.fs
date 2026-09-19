#version 330 core

out vec4 FragColor;



 

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};


struct Light {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

    in vec2 TexCoords;
    in vec3 Normal;
    in vec3 FragPos;
uniform Material material;
uniform Light light;
uniform vec3 lightPos; 
uniform vec3 viewPos; 

void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);  
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse* diff * vec3(texture(material.diffuse , TexCoords));
    //specular
    vec3 viewDir = normalize(viewPos - FragPos); // how to side of the cube look on the camera
    vec3 reflectDir = reflect(-lightDir , norm); // how to light come back to the camera
    float spec = pow(max(dot(viewDir , reflectDir),0.0),material.shininess);
    vec3 specular = material.specular * light.specular * spec;

    vec3 result = (diffuse + ambient + specular);
    FragColor = vec4(result, 1.0);
    // mix(texture(TEXTURE1 ,Tex) , texture(TEXTURE2 , Tex) ,0.2)
} 






