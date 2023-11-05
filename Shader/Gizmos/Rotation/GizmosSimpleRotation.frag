uniform float blend;
uniform vec3 color;

void main()
{
    gl_FragColor = vec4(color, blend);
}

