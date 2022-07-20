#version 460

out vec4 fragment_color;
in vec2 texture_coords;

layout (binding = 0) uniform sampler2D input_texture; 

void main()
{
    fragment_color = texture(input_texture, texture_coords);
}
 