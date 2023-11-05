uniform vec3 ColorSelection;

void main()
{
    gl_FragColor = vec4(ColorSelection[0]/255.0, ColorSelection[1]/255.0, ColorSelection[2]/255.0, 1.0);
}
