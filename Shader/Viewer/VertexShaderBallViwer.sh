attribute vec3 vertex;
attribute vec3 normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;
uniform int dir;
varying vec3 _color;
void main()
{
    vec3 v;
    if(dir==0){
        v[0] = vertex[0]+0.3;
        v[1] = vertex[1];
        v[2] = vertex[2];
    }else if(dir==1){
        v[0] = vertex[0];
        v[1] = vertex[1]+0.3;
        v[2] = vertex[2];
    }else if(dir==2){
        v[0] = vertex[0];
        v[1] = vertex[1];
        v[2] = vertex[2]+0.3;
    }else if(dir==3){
        v[0] = vertex[0]-0.3;
        v[1] = vertex[1];
        v[2] = vertex[2];
    }else if(dir==4){
        v[0] = vertex[0];
        v[1] = vertex[1]-0.3;
        v[2] = vertex[2];
    }else{
        v[0] = vertex[0];
        v[1] = vertex[1];
        v[2] = vertex[2]-0.3;
    }
    gl_Position = projection * view * model * vec4(v, 1.0);
    _color = color;
}

