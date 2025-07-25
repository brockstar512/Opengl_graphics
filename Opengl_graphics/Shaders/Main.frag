#version 400

struct Light
{
 vec3 position;
 vec3 ambient;
 vec3 diffuse;
 vec3 specular;

};

struct Material
{
	float shininess;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 colorOut;
in vec2 textureOut;
in vec3 vertexOut;

out vec4 fragColor;

uniform Material material;
uniform Light light;
uniform vec3 cameraPosition;

uniform bool isLit;
uniform bool isTextured;

uniform sampler2D textureImage;

void main()
{
    vec3 finalColor; 

    if (isLit)
    {
        vec3 normal = vec3(0.0, 1.0, 0.0);
        vec3 ambientColor = light.ambient * material.ambient;
        vec3 lightDirection = normalize(light.position - vertexOut);
        float lightIntensity = max(dot(lightDirection, normal), 0.0);
        vec3 diffuseColor = light.diffuse * material.diffuse * lightIntensity;

        vec3 viewDirection = normalize(cameraPosition - vertexOut);
        vec3 reflection = reflect(-lightDirection, normal);
        float specularTerm = pow(max(dot(viewDirection, reflection), 0.0), material.shininess);
        vec3 specularColor = light.specular * material.specular * specularTerm;

        finalColor = ambientColor + diffuseColor + specularColor;
    }
    else
    {
        finalColor = colorOut;
    }

    if (isTextured)
    {
        fragColor = vec4(finalColor, 1.0) * texture(textureImage, textureOut);
    }
    else
    {
        fragColor = vec4(finalColor, 1.0);
    }
}