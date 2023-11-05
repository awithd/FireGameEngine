uniform vec3 color;
varying vec3 normal;
uniform vec3 eye_camera;

void main()
{
    float r = dot(normal, eye_camera.xyz);
    r = acos(r);
    r = (r*180.0)/3.14159265358979323846;
    if(r>91.0){
        discard;
    }else{
        gl_FragColor = vec4(color, 1.0);
    }
}
