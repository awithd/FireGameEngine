varying vec2 TexCoords;
varying vec3 color;
varying float mode_v;

uniform sampler2D screenTexture;
uniform vec3 select_color;

void main()
{
    if(mode_v==0.0){
        gl_FragColor = texture2D(screenTexture, TexCoords);
    }else if(mode_v==1.0){
        gl_FragColor = vec4(select_color[0]/255.0, select_color[1]/255.0, select_color[2]/255.0, 1.0);
    }else if(mode_v==2.0){
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }else{
        gl_FragColor = vec4(0.0,0.0, 0.0, 1.0);
    }

}
