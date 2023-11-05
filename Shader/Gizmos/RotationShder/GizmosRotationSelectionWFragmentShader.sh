uniform vec3 color;
uniform vec3 center;
void main()
{
   float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));
   if(f < 90.0) discard;
   else if(f>=90.0 && f<93.8) gl_FragColor = vec4(color.xyz, 1.0);
   else discard;
}
