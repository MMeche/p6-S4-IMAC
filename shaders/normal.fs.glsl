#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec4 fFragColor;
uniform vec4 uColor;

void main()
{
    fFragColor = uColor;
}