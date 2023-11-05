uniform vec3 center;
uniform vec3 color;
void main()
{
    float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));
    if(f < 140.0) discard;
    else if(f>=140.0 && f<153.8) gl_FragColor = vec4(color, 1.0);
    else discard;
}

