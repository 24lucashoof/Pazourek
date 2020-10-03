#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord;
out vec4 v_colorElement;
out vec3 v_position;
out vec3 v_normal;

out vec3 testNormal;

out vec3 v_FragPos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(position, 1.0);
	v_TexCoord = texCoord;
	
	v_FragPos = vec3(u_Model * vec4(position, 1.0f));
	v_normal = inverse(transpose(mat3(u_Model))) * normal;
	testNormal = normal;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_colorElement;
in vec3 v_position;
in vec3 v_normal;

in vec3 v_FragPos;
in vec3 testNormal;

uniform sampler2D u_diffuseMap;
uniform sampler2D u_specularMap;
uniform sampler2D u_normalMap;
uniform sampler2D u_roughtnessMap;

uniform vec3 u_lightPos0;
uniform vec3 u_lightPos1;
uniform vec3 u_CameraPos;

//uniforms for testing 
uniform float u_AmbientStrength;
//uniform float u_SpecularStrength;
uniform vec3 u_lightColor;
uniform float u_Shininess;

vec3 t_normal = texture(u_normalMap, v_TexCoord).rgb;
vec3 t_diffuse = texture(u_diffuseMap, v_TexCoord).rgb;
vec3 t_specular = texture(u_specularMap, v_TexCoord).rgb;
float AO = texture(u_roughtnessMap, v_TexCoord).r;

vec3 calculateLight(vec3 lightPos, vec3 lightColor)
{
	//ambient
	float ambientStrength = u_AmbientStrength;
	vec3 ambient = vec3(ambientStrength * t_diffuse * AO);

	//diffuse
	//vec3 norm = normalize(t_normal * 2.0 - 1.0);
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(lightPos - v_FragPos);
	float diffuseStregth = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diffuseStregth * lightColor * t_diffuse;
	//
	////specular
	vec3 viewDir = normalize(u_CameraPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shininess);
	vec3 specular = spec * lightColor * t_specular;

	//result
	vec3 result = (ambient + diffuse + specular);
	return result;
}


//ligths still have to be put in here manually
#define LIGHT_COUNT = 2;

void main()
{
	vec3 result = (calculateLight(u_lightPos0, u_lightColor) + calculateLight(u_lightPos1, vec3(1.0f, 1.0f, 1.0f))) / 2;

	color = vec4(result, 1.0f);
	


}