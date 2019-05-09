#version 450 core

//shader info
uniform float iTime;
uniform vec3 iResolution;

//camera info
uniform vec3 eye;
uniform vec3 target;
uniform vec3 up;

//pixel output
out vec4 fragColor;

//parameter of the shader
const int MAX_MARCHING_STEPS = 256;
const float MIN_DIST = 0.00001;
const float MAX_DIST = 200.0;
const float EPSILON = 0.001;
const float RADIANT = 0.0174533;


// ----- Matrix operator ----
// rotation Matrix : allow object rotation
// view Matrix : allow fps camera

mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

mat4 viewMatrix(vec3 eye, vec3 center, vec3 up) 
{
    // Based on gluLookAt man page
    vec3 f = normalize(center - eye);
    vec3 s = normalize(cross(f, up));
    vec3 u = cross(s, f);
    return mat4(
        vec4(s, 0.0),
        vec4(u, 0.0),
        vec4(-f, 0.0),
        vec4(0.0, 0.0, 0.0, 1)
    );
}

// ----- DE operator -----
// smin : https://www.iquilezles.org/www/articles/smin/smin.htm
// intersectSDF : return everypoint where two object intersect
// unionSDF : return both object with a smooth min
// differenceSDF : return the difference between object A and B

float smin( float a, float b, float k )
{
    float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}

float intersectSDF(float distA, float distB) {
    return max(distA, distB);
}

float unionSDF(float distA, float distB, float k) {
    return smin(distA, distB, k);
}

float differenceSDF(float distA, float distB) {
    return max(distA, -distB);
}

// ---- Primary shape function ----
// this is for getting basic object
// and creation more complex object
// use DE operator for creatin complex object

float sphereSDF(vec3 samplePoint, float p, float s) {
    return length(samplePoint - p) - s;
}

float cylinderSDF( vec3 p, vec3 c )
{
  return length(p.xz-c.xy)-c.z;
}

float torusSDF( vec3 p, vec2 t )
{
  vec2 q = vec2(length(p.xz)-t.x,p.y);
  return length(q)-t.y;
}

float CappedCylinderSDF( vec3 p, vec2 h )
{
  vec2 d = abs(vec2(length(p.xz),p.y)) - h;
  return min(max(d.x,d.y),0.0) + length(max(d,0.0));
}

// ---- raymarching scene ----
// Here where the magic append put all
// our basic object and creation everything you need

float sceneSDF(vec3 samplePoint) {
    
   	float modu = 6.;
    
    samplePoint = mod(samplePoint, modu);
    
    float result = sphereSDF(samplePoint, modu/2, .75);
    result = unionSDF(result, CappedCylinderSDF( samplePoint - modu/2., vec2(0.25,50.)),0.25);
    
    vec4 rot = rotationMatrix(vec3(1.,0.,0.), 90. * RADIANT) * vec4(samplePoint- modu/2.,1.);
   	result = unionSDF(result, CappedCylinderSDF( rot.xyz, vec2(0.25,50.)),0.25);
    
    rot = rotationMatrix(vec3(.0,0.,1.), 90. * RADIANT) * vec4(samplePoint- modu/2.,1.);
   	result = unionSDF(result, CappedCylinderSDF( rot.xyz, vec2(0.25,50.)),0.6);
    
    return result;
}

// ---- Raymarching Algorythm ----
// shortestDistanceToSurface : it the raymarching algo
// it use sphere tracing
// rayDirection : it for the direction of the fired raymarched ray

float m = 0;

float shortestDistanceToSurface(vec3 eye, vec3 marchingDirection, float start, float end) {
    float depth = start;
    float td = 0.0;
    for (int i = 0; i < MAX_MARCHING_STEPS; i++) {
        float dist = sceneSDF(eye + depth * marchingDirection);
        if (dist < EPSILON) {
			return depth;
        }
        depth += dist;
        if (depth >= end) {
            return end;
        }
        td += MIN_DIST;

       m = min(1., 6. * MIN_DIST / td);
    }
    return end;
}
            
vec3 rayDirection(float fieldOfView, vec2 size, vec2 fragCoord) {
    vec2 xy = fragCoord - size / 2.0;
    float z = size.y / tan(radians(fieldOfView) / 2.0);
    return normalize(vec3(xy, -z));
}

// ---- Ligth Algorythm ----
// estimateNormal : https://iquilezles.org/www/articles/normalsSDF/normalsSDF.htm
// phong : https://en.wikipedia.org/wiki/Phong_shading

vec3 estimateNormal(vec3 p) {
    return normalize(vec3(
        sceneSDF(vec3(p.x + EPSILON, p.y, p.z)) - sceneSDF(vec3(p.x - EPSILON, p.y, p.z)),
        sceneSDF(vec3(p.x, p.y + EPSILON, p.z)) - sceneSDF(vec3(p.x, p.y - EPSILON, p.z)),
        sceneSDF(vec3(p.x, p.y, p.z  + EPSILON)) - sceneSDF(vec3(p.x, p.y, p.z - EPSILON))
    ));
}

vec3 phongContribForLight(vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye,
                          vec3 lightPos, vec3 lightIntensity) {
    vec3 N = estimateNormal(p);
    vec3 L = normalize(lightPos - p);
    vec3 V = normalize(eye - p);
    vec3 R = normalize(reflect(-L, N));
    
    float dotLN = dot(L, N);
    float dotRV = dot(R, V);
    
    if (dotLN < 0.0) {
        // Light not visible from this point on the surface
        return vec3(0.0, 0.0, 0.0);
    } 
    
    if (dotRV < 0.0) {
        // Light reflection in opposite direction as viewer, apply only diffuse
        // component
        return lightIntensity * (k_d * dotLN);
    }
    return lightIntensity * (k_d * dotLN + k_s * pow(dotRV, alpha));
}

vec3 phongIllumination(vec3 k_a, vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye) {
    const vec3 ambientLight = 0.6 * vec3(1.0, 1.0, 1.0);
    vec3 color = ambientLight * k_a;
    
    vec3 light1Pos = vec3(0.,0.,0.);
    
    vec3 light1Intensity = vec3(0.5, 0.5, 0.5);
    
    color += phongContribForLight(k_d, k_s, alpha, p, eye,
                                  light1Pos,
                                  light1Intensity);
  
    return color;
}

void main()
{
    // where the cam is looking in local space
	vec3 viewDir = rayDirection(90.0, iResolution.xy, gl_FragCoord.xy); 

    //get a view matrix based on world space
    mat4 viewToWorld = viewMatrix(eye,target, up);

    //where the cam is looking in world space
	vec3 worldDir = (viewToWorld * vec4(viewDir, 0.0)).xyz;
	float dist = shortestDistanceToSurface(eye, worldDir, MIN_DIST, MAX_DIST);
    
    // The closest point on the surface to the eyepoint along the view ray
    vec3 p = eye + dist * worldDir;

    vec3 K_a = vec3(0.5, 0.5, 0.5);
    vec3 K_d = vec3(1., 1., 1.);
    vec3 K_s = vec3(.5, .5, .5);
    float shininess = 10.0;
    
    vec3 color = phongIllumination(K_a, K_d, K_s, shininess, p, eye);
    
    //sky looking background
    if (dist > MAX_DIST - EPSILON) {
        // Didn't hit anything
        fragColor = vec4(0.7922, 0.9255, 0.9608, 1.);
		return;
    }

    int glowing = 10;
    if(dist < MIN_DIST)
    {
       
    }
    else
    {
        color += (1.0 - m) * (1.0 - m) * vec3(0.0745, 0.0941, 0.098);
    }
    
    fragColor = vec4(color, 1.0);

}