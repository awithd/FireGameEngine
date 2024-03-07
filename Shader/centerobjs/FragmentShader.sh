uniform float center_x;
uniform float center_y;
void main()
{
   float f = sqrt((gl_FragCoord.x-center_x)*(gl_FragCoord.x-center_x)+(gl_FragCoord.y-center_y)*(gl_FragCoord.y-center_y));

   if(f < 2.4)
       gl_FragColor = vec4(1.0, 0.749, 0.0, 1.0);
   else if(f >= 2.4 && f < 3.0)
       gl_FragColor = vec4(1.0, 0.749, 0.0, 0.3);
   else if(f >= 3.0 && f < 4.2)
       gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
   else if(f >= 4.2 && f < 4.4)
       gl_FragColor = vec4(0.5, 0.5, 0.5, 0.5);
   else if(f >= 4.4 && f < 8.2)
       gl_FragColor = vec4(1.0, 1.0, 1.0, 0.5);
   else
       discard;

}
