uniform vec3 color;
uniform float blend;
uniform vec3 center;

void main()
{
    float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));
    float w=120.0;
    gl_FragColor = vec4(color, blend);

}
