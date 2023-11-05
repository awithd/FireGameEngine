attribute vec3 VERTEX;
attribute vec3 NORMAL;
attribute vec2 TEXCOORD;

uniform mat4 ModelViewProjectionMatrix;

void main()
{
    gl_Position =  ModelViewProjectionMatrix * vec4(VERTEX, 1.0);
}
