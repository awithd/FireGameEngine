uniform float center_x;
uniform float center_y;
void main()
{
   float f = sqrt((gl_FragCoord.x-center_x)*(gl_FragCoord.x-center_x)+(gl_FragCoord.y-center_y)*(gl_FragCoord.y-center_y));

   if(f < 40.0)
       gl_FragColor = vec4(0.7, 0.7, 0.7, 0.6);
   else if(f >= 40.0 && f < 40.5)
       gl_FragColor = vec4(0.7, 0.7, 0.7, 0.3);
   else if(f >= 40.5 && f < 40.7)
       gl_FragColor = vec4(0.7, 0.7, 0.7, 0.1);
   else
       discard;
}
