#version 130

uniform int AdapteIndex;
varying float VertexID;

void main()
{
    int u_color = int(VertexID+AdapteIndex+1.0);
    float r = float(u_color / 256 / 256);
    float g = float(u_color / 256 - int(r * 256.0));
    float b = float(u_color - int(r * 256.0 * 256.0) - int(g * 256.0));

    gl_FragColor = vec4(r / 255.0, g / 255.0, b / 255.0, 1.0);
}
