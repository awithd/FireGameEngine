uniform vec3 center;
void main()
{
   float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));
   if(f < 6.0 && f > 3.0)  gl_FragColor = vec4(0.35, 0.29, 0.1, 1.0);
   else if(f <= 3.0) gl_FragColor = vec4(0.89, 0.91, 0.24, 1.0);
   else discard;
}
