attribute vec3 vertex;
attribute vec3 color;
varying vec3 _color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(vertex, 1.0);
   _color = color;
}
