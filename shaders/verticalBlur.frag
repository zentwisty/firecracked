#version 330 core

in vec2 uv;

uniform sampler2D tex;
uniform int supportWidth;

out vec4 fragColor;

void main(){
    fragColor = vec4(1.0);

    // TODO [Task 11] Calculate the texelSize
    vec2 texelSize;
    texelSize = 1.0 / textureSize(tex, 0).xy;

    const int supportWidth = 40;

    fragColor = vec4(0.0);
    float weights = 0.0;
    for (int i = -supportWidth; i <= supportWidth; i++) {
        float weight = (supportWidth + 1) - abs(i);
        // TODO [Task 11] Add weight * sampleColor to fragColor, where
        //                sampleColor = tex sampled at uv + the offset
        //                in the y direction (you are moving vertically by "i" texels)
        weights += weight;
        vec4 sampleColor;
        vec2 offset = vec2(0, texelSize.y*i);
        sampleColor = texture(tex, uv+offset);
        fragColor += weight * sampleColor;
    }
    fragColor /= weights;
}
