attribute vec3 vertex;
//uniform vec3 ref;
uniform mat4 ModelViewProjectionMatrix;
//varying float blend;

void main()
{
    gl_Position = ModelViewProjectionMatrix *  vec4(vertex, 1.0);
    //float i_x = vertex[0]-ref[0];
    //float i_z = vertex[2]-ref[2];

    //blend = 5.0/sqrt(i_x*i_x+i_z*i_z);
}
