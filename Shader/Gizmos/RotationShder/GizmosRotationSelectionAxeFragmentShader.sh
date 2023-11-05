varying vec3 _color;
varying vec3 _normal;
void main()
{
   float r = dot(_normal, vec3(0.0,0.0,1.0));
   r = acos(r);
   r = (r*180.0)/3.14159265358979323846;
   if(r<90.0 && r>-90.0){
       discard;
   }else{
       gl_FragColor = vec4(_color, 1.0);
   }
}
