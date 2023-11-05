uniform vec3 ColorWireframe;

void main()
{
    gl_FragColor = vec4(ColorWireframe[0]/255.0, ColorWireframe[1]/255.0, ColorWireframe[2]/255.0, 1.0);
}
