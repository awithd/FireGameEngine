attribute vec3 vertex;
varying vec3 normal;

uniform int mode;
uniform vec3 center;

uniform mat4 rotation;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 fz;

void main()
{
    vec4 _vertex = fz * vec4(vertex, 1.0);

    if(mode==0){
        _vertex = rotation * _vertex;
    }else if(mode==1){
        _vertex =  _vertex;
    }else if(mode==2){
        _vertex = rotation  * _vertex;
    }
    normal = normalize(vec4(model * _vertex).xyz-center);

    gl_Position = projection * view * model * _vertex;
}
