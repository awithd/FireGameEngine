uniform sampler2D img;
varying vec2 texcoord;
void main()
{
    float z_ndc  = gl_FragCoord.z * 2.0 - 1.0;
    float z_clip = z_ndc / gl_FragCoord.w;
    float depth  = (z_clip+0.1) / 10.1;
    gl_FragColor = vec4(1.00, 1.0, 0.26, 1.0);

}
