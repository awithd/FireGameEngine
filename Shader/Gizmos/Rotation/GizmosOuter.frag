uniform vec3 center;
void main()
{
    float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));
    vec3 color = vec3(0.8,0.8,0.8);
    float w=140.0;
    if(f < w) discard;
    else if(f>=(w+0.0) && f<(w+0.3)) gl_FragColor = vec4(color.xyz, 0.2);
    else if(f>=(w+0.3) && f<(w+0.8)) gl_FragColor = vec4(color.xyz, 0.3);
    else if(f>=(w+0.8) && f<(w+13.0)) gl_FragColor = vec4(color.xyz, 0.4);
    else if(f>=(w+13.0) && f<(w+13.5)) gl_FragColor = vec4(color.xyz, 0.3);
    else if(f>=(w+13.5) && f<(w+13.8)) gl_FragColor = vec4(color.xyz, 0.2);
    else discard;
}
