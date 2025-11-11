#version 330 core

//TODO: P1bTask5 - Modify shader to use position, normal and light positions to compute lighting.

// Output color
in vec2 UV;

out vec3 color;

uniform sampler2D textureSampler;

void main() {
    // Set the fragment color
    //TODO: P1bTask4 - Find a way to draw the selected part in a brighter color.
    //color = vec4(1.0);
    color = texture(textureSampler, UV).rgb;

}

