uniform vec3 center;
uniform vec3 press_select;
uniform vec3 move_select;
void main()
{
   vec3 color = vec3(0.3, 0.3, 0.3);
   float w = sqrt((press_select.x-center.x)*(press_select.x-center.x)+(press_select.y-center.y)*(press_select.y-center.y));
   float ctm = sqrt((move_select.x-center.x)*(move_select.x-center.x)+(move_select.y-center.y)*(move_select.y-center.y));

   float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));
   //if(f > w && f<(w+2.0)) gl_FragColor = vec4(color.xyz, 0.6);
   float s = (ctm/(w*2.0));
   if(f < w)  gl_FragColor = vec4(0.1, 0.7, 0.7, 0.3);
   else discard;
}
