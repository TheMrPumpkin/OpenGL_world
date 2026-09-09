#version 330 core

out vec4 FragColor;


    in vec3 Normal;
    in vec3 FragPos;
    uniform vec3 objectColor;
    uniform vec3 lightColor;
    uniform vec3 lightPos; 
    uniform vec3 viewPos; 
    


void main()
{

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos); // how to side of the cube look on the camera
    vec3 reflectDir = reflect(-lightDir , norm); // how to light come back to the camera


    float ambientStrength = 0.3; // how much the light strong
    float specularStrength = 0.5;
    float spec = pow(max(dot(viewDir , reflectDir),0.0),8);
    vec3 specular = specularStrength * lightColor * spec;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (diffuse + ambient + specular) * objectColor;
    FragColor = vec4(result, 1.0);
    // mix(texture(TEXTURE1 ,Tex) , texture(TEXTURE2 , Tex) ,0.2)
} 




