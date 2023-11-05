uniform vec3 color;

void main()
{
    //   gl_FragColor = vec4(color[0]/255.0, color[1]/255.0, color[2]/255.0, 1.0);

    gl_FragColor = vec4(color[0]/255.0, color[1]/255.0, color[2]/255.0, 1.0);
}

