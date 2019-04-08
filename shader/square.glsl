// Author: Maximilien "cewein" Nowak
// Title: Square fucntion and drawing

#version 450 core

uniform vec3 iResolution;

out vec4 FragColor;

vec3 makeSquare(vec2 coord1, vec2 coord2, vec3 color, vec2 st)
{
	vec4 square = vec4(coord1, coord2);
    vec2 rez = step(square.xy, st) * (step(square.zw, st) - 1.);
    return (rez.x * rez.y) * color;
}

vec3 makeSquareF(vec2 centre, float h, float l)
{
	//need to do square with floor
    return vec3(0.);
}


void main() {
    vec2 st = gl_FragCoord.xy/iResolution.xy;
    st.x *= iResolution.x/iResolution.y;
    
    vec3 color = vec3(0.);

   vec3 result = makeSquare(vec2(0.120,0.090), vec2(0.940,0.240), vec3(0.132,0.074,1.000), st);
    result += makeSquare(vec2(0.530,0.290), vec2(0.940,0.490), vec3(1.000,0.951,0.368), st);
    result += makeSquare(vec2(0.090,0.300), vec2(0.430,0.950), vec3(0.418,1.000,0.346), st);
    result += makeSquare(vec2(0.480,0.540), vec2(0.950,0.990), vec3(1.000,0.297,0.363), st);
    
    color = vec3(result);

    FragColor = vec4(color,1.0);
}

