uniform samplerCube EnvMap;

varying vec3 texcoord;
void main (void)
{
    vec3 envColor = vec3 (textureCube(EnvMap, texcoord));
    gl_FragColor = vec4 (envColor, 1.0);
}
