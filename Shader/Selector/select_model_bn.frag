varying vec2 TexCoords;
varying vec3 color;

uniform sampler2D screenTexture;
void main()
{
   gl_FragColor = texture2D(screenTexture, TexCoords);
   //gl_FragColor = vec4(0.0,0.0, 0.0, 1.0);

}
