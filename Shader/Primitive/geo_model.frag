varying vec2 TexCoords;
uniform sampler2D screenTexture;

uniform vec3 select_color;
varying float mode_v;

void main()
{



   if(mode_v==0.0){
       vec4 texColor = texture2D(screenTexture, TexCoords);

       gl_FragColor = texColor;
   }else if(mode_v==1.0){
       gl_FragColor = vec4(select_color[0]/255.0, select_color[1]/255.0, select_color[2]/255.0, 1.0);
   }else if(mode_v==2.0){
       gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
   }else{
       gl_FragColor = vec4(0.0,0.0, 0.0, 1.0);
   }
}
