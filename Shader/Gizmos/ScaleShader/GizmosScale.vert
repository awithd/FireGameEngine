attribute vec3 vertex;

varying vec4 _color;

uniform int mode;
uniform float blend;
uniform mat4 rotation;
uniform mat4 fz;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 ver;
    if(mode==0){
        ver = rotation * fz * vec4(vertex, 1.0);
        _color = vec4(1.0, 0.0, 0.0, blend);
    }else if(mode==1){
        ver =  rotation  * fz * vec4(vertex, 1.0);
        _color = vec4(0.0, 1.0, 0.0, blend);
    }else if(mode==2){
        ver = rotation  * fz * vec4(vertex, 1.0);
        _color = vec4(0.0, 0.0, 1.0, blend);
    }
    gl_Position = projection * view * model * ver;
}
