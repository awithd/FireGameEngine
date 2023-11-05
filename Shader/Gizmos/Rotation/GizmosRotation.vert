attribute vec3 vertex;
varying vec4 _color;
varying vec3 normal;
uniform int mode;
uniform float blend;
uniform mat4 modelrotationfz;
uniform mat4 projectionview;
uniform vec3 center;

void main()
{
    vec4 _vertex =  vec4(vertex, 1.0);
    _vertex = modelrotationfz * _vertex;
    if(mode==0){
        _color = vec4(1.0, 0.0, 0.0, blend);
    }else if(mode==1){
        _color = vec4(0.0, 1.0, 0.0, blend);
    }else if(mode==2){
        _color = vec4(0.0, 0.0, 1.0, blend);
    }

    normal = normalize(_vertex.xyz-center);

    gl_Position = projectionview * _vertex;
}
