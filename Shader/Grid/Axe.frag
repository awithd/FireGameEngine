
uniform vec3 color;
//varying float blend;

uniform float distance;
uniform float scl;
uniform vec3 ccp;

float near = 1.0;
float far  = 100.0;
float LinearizeDepth(float depth)
{
    float z = 1.0-depth * 2.0 ; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}
void main()
{
    //float depth = LinearizeDepth(gl_FragCoord.z);


    ///float depth = LinearizeDepth(gl_FragCoord.z);
    ///float fog = length(vec3(gl_FragCoord.x, gl_FragCoord.y, depth)-vec3(0.0, 0.0, 0.0));
    //fog = 1.0-(fog*0.001);
    //float depth = LinearizeDepth(gl_FragCoord.z) / far;
    /*if(gl_FragCoord.z>0.02999) {
        gl_FragColor = vec4(vec3(1.0), 1.0);
    }else discard;*/

    //float fog = (0.055/(((distance)-gl_FragCoord.z)*100.0)/*(gl_FragCoord.z*100.0)*/);
    //float fct = scl*(100.0/(distance*1.0));
    //float fct ;
    //float alpha = (5.0/(fog*fog));
    //if(alpha>0.4) alpha = 0.2;

    float depth = (100.0*(1.0-gl_FragCoord.z)); //0.3
    depth = (0.3-depth);
    depth = (depth*3.0);

    //if(depth>0.1) discard;

    float fog = length(vec3(gl_FragCoord.x, gl_FragCoord.y, depth)-vec3(ccp[0], ccp[1], ccp[2]));

    //fog = 1.0-(fog*0.001);

    //if(fog>100.0) discard;

    //fog = fog;

    //if(r>0.999) discard;
    //if(r<0.997) discard;
        gl_FragColor = vec4(color, (0.9-depth));

    //gl_FragColor = vec4(vec3(color), 1-(depth/150.0));
    //gl_FragColor = vec4(vec3(depth), 1.0);
    //gl_FragColor = vec4(vec3(0.1*depth), 1.0);
    //gl_FragColor = vec4(color, 1.0);
}
