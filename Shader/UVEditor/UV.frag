#version 130

uniform vec3 ColorWireframe;

void main()
{
    gl_FragColor = vec4(ColorWireframe, 1.0);
}
