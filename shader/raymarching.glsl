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
const float MIN_DIST = 0.0001;
const float MAX_DIST = 200.0;
const float EPSILON = 0.001;
const float RADIANT = 0.0174533;

#define LIGHT 1


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

float sphereSDF(vec3 samplePoint, vec3 p, float s) {
    return length(samplePoint - p) - s;
}

float cylinderSDF( vec3 samplePoint, vec3 p, mat4 rot ,vec3 c )
{
    vec3 smp = vec4(rot*vec4(samplePoint - p,1.)).xyz;
    return length(smp.xz-c.xy)-c.z;
}

float torusSDF( vec3 samplePoint, vec3 p, mat4 rot, vec2 t )
{
    vec3 smp = vec4(rot*vec4(samplePoint - p,1.)).xyz;
    vec2 q = vec2(length(smp.xz)-t.x,smp.y);
    return length(q)-t.y;
}

float CappedCylinderSDF( vec3 samplePoint, vec3 p, mat4 rot, vec2 h )
{
    vec3 smp = vec4(rot*vec4(samplePoint - p,1.)).xyz;
    vec2 d = abs(vec2(length(smp.xz),smp.y)) - h;
    return min(max(d.x,d.y),0.0) + length(max(d,0.0));
}

float planeSDF( vec3 p )
{
	return p.y;
}

// ---- body function ----
// here for creating a monster
// base picture : http://diaryofinhumanspecies.com/WordPress/wp-content/gallery/last/raignee.jpg

float leg(vec3 samplePoint, vec3 p, bool reverse)
{
    vec3 smp = samplePoint - p;

	float side = 1.0;
	if(reverse) side = -1.0;

    mat4 base = rotationMatrix(vec3(1.,0.,0.), RADIANT * 90.);
    
    float result = CappedCylinderSDF(smp, vec3(0., -.9, 0.), base, vec2(0.150,0.7));
	 
	 mat4 b1 = rotationMatrix(vec3(1.,0.,0.), RADIANT * -60.*side);

	 result = unionSDF(result, CappedCylinderSDF(smp, vec3(0., -.65, -1*side), b1, vec2(0.150,0.7)), 0.5);

	b1 = rotationMatrix(vec3(1.,0.,0.), RADIANT * 60.*side);

	result = unionSDF(result, CappedCylinderSDF(smp, vec3(0., -.65, -2.*side), b1, vec2(0.150,0.7)), 0.2);

	b1 = rotationMatrix(vec3(1.,0.,0.), RADIANT * -10*side);

	result = unionSDF(result, CappedCylinderSDF(smp, vec3(0., -1.45, -2.45*side),  b1, vec2(0.12,0.5)), 0.3);

    return result;
}

float body(vec3 samplePoint, vec3 p)
{
    vec3 smp = samplePoint - p;

    float result = sphereSDF(smp, vec3(0.,0.3,0.), 1.3);
    result = unionSDF(result, sphereSDF(smp, vec3(1.7,0.,0.), 1.10), 1.);
    result = unionSDF(result, sphereSDF(smp, vec3(0.,1.00,0.), 0.6),0.7);
    result = unionSDF(result, sphereSDF(smp, vec3(-.5,1.00,0.), 0.40),0.7);

    return result;
}

float eyes(vec3  samplePoint, vec3 p)
{
	vec3 smp = samplePoint - p;

	float result = sphereSDF(smp, vec3(-0.9,0.4,0.), 0.65);

	mat4 b1 = rotationMatrix(vec3(0.,0.,1.), RADIANT * 90);

	result = unionSDF(result, torusSDF(smp, vec3(-1.15,0.4,0.), b1, vec2(0.575,0.07)), 0.);

	return result;
}

// ---- raymarching scene ----
// Here where the magic append put all
// our basic object and creation everything you need

float sceneSDF(vec3 samplePoint) {
    
   	float modu = 6.;

	//samplePoint.x += iTime * 5.f;
    
    samplePoint = mod(samplePoint + modu/2., vec3(1000.,10000.,6.)) - modu/2.;

	//body
    float result = body(samplePoint, vec3(0.));
    
	//leg
	vec3 smp = vec4(rotationMatrix(vec3(1.,0.,0.), RADIANT * 5 * sin(iTime * 5.)) * vec4(samplePoint,1.0)).xyz;
    result = unionSDF(result, leg(smp, vec3(0.),false), 0.05);
    result = unionSDF(result, leg(smp, vec3(0.),true), 0.05);

	smp = vec4(rotationMatrix(vec3(1.,0.,0.), RADIANT * -5 * sin(iTime * 5.)) * vec4(samplePoint,1.0)).xyz;
	result = unionSDF(result, leg(smp, vec3(1,0.,0.),false), 0.05);
	result = unionSDF(result, leg(smp, vec3(1,0.,0.),true), 0.05);

	smp = vec4(rotationMatrix(vec3(1.,0.,0.), RADIANT * 5 * sin(iTime * 5.)) * vec4(samplePoint,1.0)).xyz;
	result = unionSDF(result, leg(smp, vec3(2,0.,0.),false), 0.05);
	result = unionSDF(result, leg(smp, vec3(2,0.,0.),true), 0.05);
	
	//eyes ? jk there is only one eye
	result = unionSDF(result,eyes(samplePoint,vec3(0.)),0.05);


	//floor
	result = unionSDF(result,planeSDF(samplePoint + 2.0),0.);

    
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

#if LIGHT == 1
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
    vec3 L = normalize(lightPos);
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
    
    vec3 light1Pos = vec3(5.,5.,0.);
    
    vec3 light1Intensity = vec3(0.5, 0.5, 0.5);
    
    color += phongContribForLight(k_d, k_s, alpha, p, eye,
                                  light1Pos,
                                  light1Intensity);
  
    return color;
}
#endif
#if LIGHT == 2
// ---- Shadow algorythm ----
// https://www.iquilezles.org/www/articles/rmshadows/rmshadows.htm

float calcSoftshadow( in vec3 ro, in vec3 rd, in float mint, in float tmax, int technique )
{
	float res = 1.0;
    float t = mint;
    float ph = 1e10; // big, such that y = 0 on the first iteration
    
    for( int i=0; i<32; i++ )
    {
		float h = sceneSDF( ro + rd*t );

        // traditional technique
        if( technique==0 )
        {
        	res = min( res, 10.0*h/t );
        }
        // improved technique
        else
        {
            // use this if you are getting artifact on the first iteration, or unroll the
            // first iteration out of the loop
            //float y = (i==0) ? 0.0 : h*h/(2.0*ph); 

            float y = h*h/(2.0*ph);
            float d = sqrt(h*h-y*y);
            res = min( res, 10.0*d/max(0.0,t-y) );
            ph = h;
        }
        
        t += h;
        
        if( res<0.0001 || t>tmax ) break;
        
    }
    return clamp( res, 0.0, 1.0 );
}

vec3 calcNormal( in vec3 pos )
{
    vec2 e = vec2(1.0,-1.0)*0.5773*0.0005;
    return normalize( e.xyy*sceneSDF( pos + e.xyy ) + 
					  e.yyx*sceneSDF( pos + e.yyx ) + 
					  e.yxy*sceneSDF( pos + e.yxy ) + 
					  e.xxx*sceneSDF( pos + e.xxx ) );
}

float castRay( in vec3 ro, in vec3 rd )
{
    float tmin = MIN_DIST;
    float tmax = MAX_DIST;
    
    float t = tmin;
    for( int i=0; i<64; i++ )
    {
	    float precis = 0.0005*t;
	    float res = sceneSDF( ro+rd*t );
        if( res<precis || t>tmax ) break;
        t += res;
    }

    if( t>tmax ) t=-1.0;
    return t;
}

float calcAO( in vec3 pos, in vec3 nor )
{
	float occ = 0.0;
    float sca = 1.0;
    for( int i=0; i<5; i++ )
    {
        float h = 0.001 + 0.15*float(i)/4.0;
        float d = sceneSDF( pos + h*nor );
        occ += (h-d)*sca;
        sca *= 0.95;
    }
    return clamp( 1.0 - 1.5*occ, 0.0, 1.0 );    
}

vec3 render( in vec3 ro, in vec3 rd, in int technique)
{ 
    vec3  col = vec3(0.0);
    float t = castRay(ro,rd);

    if( t>-0.5 )
    {
        vec3 pos = ro + t*rd;
        vec3 nor = calcNormal( pos );
        
        // material        
		vec3 mate = vec3(0.3);

        // key light
        vec3  lig = normalize( vec3(5., 5., 0.) );
        vec3  hal = normalize( lig-rd );
        float dif = clamp( dot( nor, lig ), 0.0, 1.0 ) * 
                    calcSoftshadow( pos, lig, MIN_DIST, MAX_DIST, technique );

		float spe = pow( clamp( dot( nor, hal ), 0.0, 1.0 ),16.0)*
                    dif *
                    (0.04 + 0.96*pow( clamp(1.0+dot(hal,rd),0.0,1.0), 5.0 ));

		col = mate * 4.0*dif*vec3(1.00,0.70,0.5);
        col +=      12.0*spe*vec3(1.00,0.70,0.5);
        
        // ambient light
        float occ = calcAO( pos, nor );
		float amb = clamp( 0.5+0.5*nor.y, 0.0, 1.0 );
        col += mate*amb*occ*vec3(0.0,0.08,0.1);
        
    }

	return col;
}
#endif

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

    #if LIGHT == 1
    vec3 color =  phongIllumination(K_a, K_d, K_s, shininess, p, eye);
	#else
	vec3 color = render(eye, worldDir, 0);
	color = pow( color, vec3(0.4545) );
	#endif

	
    
    //sky looking background
    if (dist > MAX_DIST - EPSILON) {
        // Didn't hit anything
        fragColor = vec4(0.7922, 0.9255, 0.9608, 1.);
		return;
    }

    int glowing = 10;
    if(dist < MIN_DIST);
    else
        color += (1.0 - m) * (1.0 - m) * vec3(0.0745, 0.0941, 0.098);
    
    fragColor = vec4(color, 1.0);

}