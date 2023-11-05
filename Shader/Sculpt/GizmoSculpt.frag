uniform vec3 color;
uniform float blend;
uniform float radius;
uniform vec3 center;

void main()
{


    float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));

    if(radius<=1.0 && radius>0.0) gl_FragColor = vec4(0.0, 0.7, 0.7, 1.0);
    else if(f<=(radius-1.0)) gl_FragColor = vec4(0.0, 0.7, 0.7, 0.5);
    else if(f<radius && f>(radius-1.0)) gl_FragColor = vec4(0.0, 0.7, 0.7, 1.0);
    else discard;

}
