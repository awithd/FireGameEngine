varying vec4 _color;
varying vec3 normal;
uniform vec3 eye_camera;
uniform mat4 model;

void main()
{
    float r = dot(normal, eye_camera.xyz);
    r = acos(r);
    r = (r*180.0)/3.14159265358979323846;
    if(r>91.0){
        discard;
    }else{
        gl_FragColor = _color;
    }
}
