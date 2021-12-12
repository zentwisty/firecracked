#version 330 core

// output from quad.vert
in vec2 uv;

uniform sampler2D particleColor;
uniform sampler2D blurColor;
uniform float blurIntensity;

out vec3 fragColor;

void main(){
    fragColor = texture(particleColor, uv).xyz + blurIntensity*texture(blurColor, uv).xyz;
}
