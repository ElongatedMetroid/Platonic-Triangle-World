#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    /*
    The final output color is now the combination of two texture lookups. GLSL’s built-in mix
    function takes two values as input and linearly interpolates between them based on its third argument.
    If the third value is 0.0 it returns the first input; if it’s 1.0 it returns the second input value. A
    value of 0.2 will return 80% of the first input color and 20% of the second input color, resulting in
    a mixture of both our textures.
    */
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);      //the final output color is now a combination of two texture lookups
}