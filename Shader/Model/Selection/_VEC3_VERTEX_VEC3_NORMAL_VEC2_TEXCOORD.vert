attribute vec3 VERTEX;
uniform mat4 ModelViewProjectionMatrix;
void main()
{
    gl_Position =  ModelViewProjectionMatrix * vec4(VERTEX, 1.0);
}
