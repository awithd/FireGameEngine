#version 130

uniform int mode;
uniform float SelectedLine[128];
uniform int SelectedLineSize;
uniform vec3 ColorWireframe;

varying float IDLINE;

uniform float Seam[1024];
uniform int SeamSize;


bool check(){
    for(int i=0; i<SelectedLineSize; i++){
        if(SelectedLine[i]==IDLINE){
            return true;
        }
    }

    return false;
}

bool checkSeam(){
    for(int i=0; i<SeamSize; i++){
        if(Seam[i]==IDLINE){
            return true;
        }
    }

    return false;
}

void main()
{
    bool stsm = checkSeam();
    if(stsm){
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }else{
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
            float r = float(IDLINE / 256 / 256);
            float g = float(IDLINE / 256 - int(r * 256.0));
            float b = float(IDLINE - int(r * 256.0 * 256.0) - int(g * 256.0));
            gl_FragColor = vec4(r, g, b, 1.0);
        }
    }
}
