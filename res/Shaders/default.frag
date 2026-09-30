
#version 330 core
out vec4 FragColor;
in vec3 VertexColor;
in vec2 TexUV;

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = texture(texture_diffuse1, TexUV) * vec4(VertexColor, 1.0f);
} 