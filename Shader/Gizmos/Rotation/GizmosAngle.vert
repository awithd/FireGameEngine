attribute vec3 vertex;
uniform mat4 projection;

void main()
{
    vec4 _vertex = vec4(vertex, 1.0);
    gl_Position = projection * _vertex;
}

