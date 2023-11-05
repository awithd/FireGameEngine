#version 130

attribute float ID;
attribute vec3 VERTEX;
attribute vec3 COLOR;

uniform int mode;
uniform mat4 ModelViewProjectionMatrix;

varying float IDPOINT;

void main()
{
    gl_Position =  ModelViewProjectionMatrix * vec4(VERTEX, 1.0);
    if(mode==3 || mode==0){
        IDPOINT = ID;
    }
}
