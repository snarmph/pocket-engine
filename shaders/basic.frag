#version 330 core
out vec4 frag_color;

in vec2 tex_coords;

uniform sampler2D txt;

void main() {
    frag_color = texture(txt, tex_coords);
    if(frag_color.a < 0.1) discard;
} 