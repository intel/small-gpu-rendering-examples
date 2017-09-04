#version 150
#define MAX_STEPS 64
#define EPSILON 0.001

#define CAMERA vec3(0.5,0.2,-1)
// canvas size, hardcoded for simplicity
#define WIDTH 800
#define HEIGHT 800

#define LIGHT_POSITION vec3(1, 0.8, -0.8)
#define LIGHT_COLOR vec3(1, 1, 1)
#define AMBIENT_LIGHT_STRENGTH 0.1
#define SPECULAR_LIGHT_STRENGTH 0.1
#define SPECULAR_LIGHT_SHININESS 128


out vec4 outColor;

// Signed distance function for a single sphere.
float signedDistanceSphere(vec3 position, vec3 center, float radius) {
    return distance(position, center) - radius;
}

// Signed distance function for a box.
float signedDistanceBox(vec3 position, vec3 center, vec3 size) {
    vec3 v = max(position - center - size/2.0, center - position - size/2.0);
    return max(max(v.x, v.y), v.z);
}

// Get a minimum of 4 numbers.
float min4(float a, float b, float c, float d) {
    return min(min(min(a, b), c), d);
}

// Signed distance function for some objects - negative when inside of some
// object, positive when outside, zero on the boundary.
// TODO: use the model matrix to move around the objects
float signedDistance(vec3 position) {
    vec3 center = vec3(0, 0, 0.3);
    float sphere_radius = 0.2;
    return min4(
               signedDistanceSphere(position - vec3(0.1, 0, 0),
                                    center,
                                    sphere_radius),
               signedDistanceSphere(position + vec3(0.1, 0, 0),
                                    center,
                                    sphere_radius),
               signedDistanceSphere(position + vec3(0, 0.15, 0),
                                    center,
                                    sphere_radius),
               signedDistanceBox(position + vec3(0.4, 0.3, 0.1),
                                    center,
                                    vec3(0.2, 0.3, 0.1))
    );
}

// Guess what the normal of the surface is at this position by looking at nearby
// points on the surface.
vec3 estimateNormal(vec3 position) {
    vec3 normal;
    normal.x = signedDistance(position + vec3(EPSILON, 0, 0))
             - signedDistance(position - vec3(EPSILON, 0, 0));
    normal.y = signedDistance(position + vec3(0, EPSILON, 0))
             - signedDistance(position - vec3(0, EPSILON, 0));
    normal.z = signedDistance(position + vec3(0, 0, EPSILON))
             - signedDistance(position - vec3(0, 0, EPSILON));
    return normalize(normal);
}

// Calculate Phong lighting for a single point at position.
// https://learnopengl.com/#!Lighting/Basic-Lighting
vec4 light(vec3 position, vec3 normal) {
    vec3 lightDirection = normalize(LIGHT_POSITION - position);
    vec3 reflectionDirection = reflect(lightDirection, normal);
    vec3 viewDirection = normalize(position - CAMERA);
    vec3 objectColor = vec3(0,1,1);

    vec3 ambient = AMBIENT_LIGHT_STRENGTH * LIGHT_COLOR;
    vec3 diffuse = max(dot(normal, lightDirection), 0) * LIGHT_COLOR;
    float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0),
                     SPECULAR_LIGHT_SHININESS);
    vec3 specular = SPECULAR_LIGHT_STRENGTH * spec * LIGHT_COLOR;
    return vec4(objectColor * (ambient + diffuse + specular), 1);
}

// Return the color of the object at this position.
vec4 renderSurface(vec3 position, vec3 viewDirection) {
    vec3 normal = estimateNormal(position);
    return light(position, normal);
}

// Figure out the color of the current fragment by casting a ray from the camera
// trough the current gl_FragCoord. Move along the ray by a step equal to the
// distance to the nearest surface, given by the signed distance function, until
// we hit some surface.
// http://www.alanzucconi.com/2016/07/01/raymarching/
vec4 raymarch() {
    // each pixel gets a coordinate between (-1,-1) and (1,1)
    vec2 coord = vec2((gl_FragCoord.x - (WIDTH/2)) / WIDTH,
                      (gl_FragCoord.y - (HEIGHT/2)) / HEIGHT);
    vec3 position = vec3(coord, 0);
    vec3 viewDirection = normalize(position - CAMERA);

    for (int i = 0; i < MAX_STEPS; i++) {
        float dist = signedDistance(position);
        if (dist <= EPSILON) {
            return renderSurface(position, viewDirection);
        } else {
            position += dist * viewDirection;
        }
    }
    return vec4(0,0,0,1); // black
}


void main() {
    outColor = raymarch();
}
