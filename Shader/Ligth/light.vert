attribute vec2 vertex;
attribute vec2 UV;
varying vec2 texcoord;
uniform mat4 model;
uniform mat4 projection;
void main()
{
    gl_Position =  projection*model*vec4(vertex, -0.1, 1.0);
    texcoord = UV;
}
