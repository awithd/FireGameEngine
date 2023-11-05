varying vec2 TexCoords;
uniform sampler2D screenTexture;
void main()
{
   gl_FragColor = texture2D(screenTexture, TexCoords);
   //gl_FragColor = vec4(1.0, 0.5, 1.0, 1.0);
   /*vec3 col = texture2D(screenTexture, TexCoords).rgb;
   gl_FragColor = vec4(col, 1.0);*/
}
