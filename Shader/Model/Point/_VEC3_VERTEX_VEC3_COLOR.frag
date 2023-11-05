#version 130

uniform int mode;
uniform float SelectedPoint[128];
uniform int SelectedPointSize;
uniform vec3 ColorWireframe;

varying float IDPOINT;



bool check(){
    for(int i=0; i<SelectedPointSize; i++){
        if(SelectedPoint[i]==IDPOINT){
            return true;
        }
    }

    return false;
}


void main()
{
    bool st = check();
    if(mode==0){
        if(st){
            gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
        }else{
            gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        }
    }else if(mode==1){
        gl_FragColor = vec4(ColorWireframe[0]/255.0, ColorWireframe[1]/255.0, ColorWireframe[2]/255.0, 1.0);
    }else if(mode==3){ // PICK MODE
        float r = float(IDPOINT / 256 / 256);
        float g = float(IDPOINT / 256 - int(r * 256.0));
        float b = float(IDPOINT - int(r * 256.0 * 256.0) - int(g * 256.0));
        gl_FragColor = vec4(r, g, b, 1.0);
    }
}
