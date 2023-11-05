uniform vec3 color;
uniform vec3 center;
void main()
{
   float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));
   gl_FragColor = vec4(color.xyz, 0.2);
   else if(f>=70.0 && f<70.5) gl_FragColor = vec4(color.xyz, 0.1);
   else if(f>=70.5 && f<70.8) gl_FragColor = vec4(color.xyz, 0.05);
   else discard;
}
