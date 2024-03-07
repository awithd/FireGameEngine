attribute vec2 VERTEX;
attribute vec2 TEXTCOORD;
varying vec2 TexCoords;
uniform mat4 ModelViewProjectionMatrix;

void main()
{
    TexCoords = TEXTCOORD;
    gl_Position =  ModelViewProjectionMatrix *vec4(VERTEX.x, VERTEX.y, 0.0, 1.0);
}
