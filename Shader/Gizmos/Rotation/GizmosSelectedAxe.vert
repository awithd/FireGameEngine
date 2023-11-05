attribute vec3 vertex;
uniform int mode;
uniform mat4 rotation;
uniform mat4 model;
uniform mat4 view;
uniform mat4 fz;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * fz * rotation * vec4(vertex, 1.0);
}
