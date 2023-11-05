uniform vec3 color;

float near = 0.02;
float far  = 0.1;
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}
void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
   gl_FragColor = vec4(vec3(color), 1.0-(depth*3.7));
}
