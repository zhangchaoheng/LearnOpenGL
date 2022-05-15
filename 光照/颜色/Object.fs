#version 330 core

out vec4 Fragment;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main(){
	Fragment = vec4(objectColor * lightColor, 1);
}