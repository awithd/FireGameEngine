varying vec3 _color;
uniform float blend;
void main()
{
   gl_FragColor = vec4(_color, blend);
}
