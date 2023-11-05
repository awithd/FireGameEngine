attribute vec3 vertex;
uniform vec3 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
varying vec3 _color;
void main()
{
   gl_Position = projection * view * model * vec4(vertex, 1.0);
   _color = color;
}
