#version 330 core
out vec4 frag_color;

in vec2 tc;
uniform sampler2D txt;

void main() {
    frag_color = texture(txt, tc) - vec4(0.0, 0.0, 0.0, 0.0);
    // TODO remove this
    if(frag_color.a < 1.0)
        discard;
}

