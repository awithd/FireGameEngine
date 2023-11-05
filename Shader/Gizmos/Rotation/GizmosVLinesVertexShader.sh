attribute vec3 vertex;
uniform mat4 view;
uniform mat4 fz;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view *fz* vec4(vertex, 1.0);
}
