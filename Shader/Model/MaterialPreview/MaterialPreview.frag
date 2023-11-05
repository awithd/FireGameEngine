#version 330
out vec4 FragColor;

uniform sampler2D ScreenTexture;
uniform float opacity;
uniform float black;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec4 CustomColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in float _IDFace;

uniform PointLight pointLights[128];
uniform int size_light;
uniform vec3 viewPos;
uniform float SelectedFace[128];
uniform int SelectedFaceSize;


// function prototypes
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

bool check(){
    for(int i=0; i<SelectedFaceSize; i++){
        if(SelectedFace[i]==_IDFace){
            return true;
        }
    }

    return false;
}
/*

void main()
{    gl_FragColor = texture2D(ScreenTexture, TexCoords);

    //gl_FragColor = vec4(0.3, 0.2, 1.8, 1.0);
}*/

void main()
{
    bool st = check();
    if(black==1.0){
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }else if(black==2.0){
        if(st){
            FragColor = vec4(0.5, 0.5, 0.5, 0.5);
        }else{
            FragColor = vec4(0.3, 0.3, 0.3, 1.0);
        }

    }else{
        if(st){
            FragColor = vec4(1.0, 1.0, 0.0, 0.5);
        }else{
            vec3 norm = normalize(Normal);
            vec3 viewDir = normalize(viewPos - FragPos);

            vec3 result = vec3(0.0, 0.0, 0.0);
            // phase 2: point lights
            for(int i = 0; i < size_light; i++)
                result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
            result = result*opacity;

            FragColor = vec4(result, 1.0);
            //gl_FragColor = vec4(0.7, 0.7, 0.7, 1.0);
        }

    }

}



// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4.0);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 2.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = 1.6*light.ambient * vec3(texture2D(ScreenTexture, TexCoords));
    vec3 diffuse = light.diffuse * diff  * vec3(texture2D(ScreenTexture, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture2D(ScreenTexture, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
