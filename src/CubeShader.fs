#version 330 core

out vec4 FragColor;



uniform vec3 objectColor;
uniform vec3 lightColor;



void main()
{
    
    FragColor = vec4(objectColor * lightColor , 1.0);;
    // mix(texture(TEXTURE1 ,Tex) , texture(TEXTURE2 , Tex) ,0.2)
} 