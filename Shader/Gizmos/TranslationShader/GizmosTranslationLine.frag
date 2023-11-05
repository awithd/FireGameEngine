uniform vec3 color;
uniform float blend;
void main()
{
   gl_FragColor = vec4(color, blend);
}
