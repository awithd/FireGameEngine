#version 130

uniform float SelectedPoint[128];
uniform int SelectedPointSize;
uniform vec3 ColorPoint;

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
    if(st){
        gl_FragColor = vec4(1.0, 0.4, 0.0, 1.0);
    }else{
        gl_FragColor = vec4(ColorPoint, 1.0);
    }
}
