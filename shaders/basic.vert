#version 330 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 in_tex_coords;

out vec2 tex_coords;

uniform mat3 projection;
uniform vec2 scale;
uniform vec2 position;

void main() {
    vec3 pos = vec3(vertex * scale  + position, 1.0);
    gl_Position = vec4(projection * pos, 1.0);
    tex_coords = in_tex_coords;
}