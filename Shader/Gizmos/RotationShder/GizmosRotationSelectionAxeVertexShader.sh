attribute vec3 vertex;
attribute vec3 normal;
uniform vec3 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
varying vec3 _color;
varying vec3 _normal;
void main()
{
   gl_Position = projection * view * model * vec4(vertex, 1.0);
   vec4 n = projection * view * model * vec4(normal, 1.0);
   _color = color;
   _normal = n.xyz;
}
