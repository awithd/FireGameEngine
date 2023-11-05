attribute vec3 vertex;
uniform mat4 view;
uniform mat4 projection;
uniform float blend;
uniform vec3 color;
varying vec4 _color;

void main()
{
    gl_Position = projection * view * vec4(vertex, 1.0);
    _color = vec4(color, blend);
}
