attribute vec3 aPos;
attribute vec2 aTexCoords;
varying vec2 Texcoord;
void main()
{
    Texcoord = aTexCoords;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

