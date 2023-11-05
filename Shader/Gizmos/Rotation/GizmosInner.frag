uniform vec3 center;
void main()
{
    float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));
    float w=104.0;
    if(f<w) gl_FragColor = vec4(0.8,0.6,0.3,0.1);
    else discard;
}
