#version 330 core

out vec4 FragColor;
in vec2 Tex;


uniform sampler2D TEXTURE1;
uniform sampler2D TEXTURE2;


void main()
{
    
    FragColor = mix(texture(TEXTURE1 ,Tex) , texture(TEXTURE2 , Tex) ,0.2);
} 