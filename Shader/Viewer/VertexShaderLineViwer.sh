attribute vec3 vertex;
attribute float color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
varying vec3 _color;
void main()
{
    gl_Position = projection * view * model * vec4(vertex, 1.0);
    if(color==3.0){
        _color = vec3(1.0, 0.0, 0.0);
    }else if(color==1.0){
        _color = vec3(0.0, 1.0, 0.0);
    }else{
        _color = vec3(0.0, 0.0, 1.0);
    }
}
