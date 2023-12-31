attribute vec3 vertex;
uniform mat4 ModelViewProjectionMatrix;

void main()
{
    gl_Position = ModelViewProjectionMatrix * vec4(vertex, 1.0);
}
