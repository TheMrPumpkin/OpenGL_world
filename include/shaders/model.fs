
out vec4 FragColor;

uniform sampler2D texture_diffuse1;


void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos); // how to side of the cube look on the camera
    vec3 result = CalDirLight(dirLight , norm ,  viewDir);
    
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += CalPointLight(pointLights[i], norm, viewDir, FragPos);
    }

    result += CalSpotLight(spotLight, norm ,  viewDir , FragPos);

    FragColor = texture(texture_diffuse1, TexCoords) * vec4(result , 1.0);
    // mix(texture(TEXTURE1 ,Tex) , texture(TEXTURE2 , Tex) ,0.2)
}