#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec2 resolution;  // Résolution interne pour l'effet pixelisé
uniform int pixelSize;    // Taille des pixels artificiels

out vec4 finalColor;

void main()
{
    vec2 pixelatedUV = floor(fragTexCoord * resolution / pixelSize) * pixelSize / resolution;
    vec4 texColor = texture(texture0, pixelatedUV);
    
    finalColor = texColor * fragColor;
}
