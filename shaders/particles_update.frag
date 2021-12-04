#version 330 core

uniform float firstPass;
uniform sampler2D prevPos;
uniform sampler2D prevVel;
uniform int numParticles;
uniform float dt;

// output from quad.vert
in vec2 uv;

// TODO [Task 15] setup the output locations
layout(location = 0) out vec4 pos;
layout(location = 1) out vec4 vel;

const float PI = 3.14159;

/*
    A particle has the following properties:
        - pos.xyz = clip space position
        - pos.w = lifetime in seconds (doesn't change)
        - vel.xyz = clip space velocity
        - vel.w = current age in seconds
*/

// A helpful procedural "random" number generator
float hash(float n) { return fract(sin(n)*753.5453123); }

// Helper functions to procedurally generate lifetimes and initial velocities
// based on particle index
float calculateLifetime(int index) {
    const float MAX_LIFETIME = 1.0;
    const float MIN_LIFETIME = 0.5;
    return MIN_LIFETIME + (MAX_LIFETIME - MIN_LIFETIME) * hash(index * 2349.2693);
}

vec2 calculateInitialVelocity(int index) {
    float theta = 2*PI * hash(index * 872.0238);
    const float MAX_VEL = 0.3;
    float velMag = MAX_VEL * hash(index * 98723.345);
    return velMag * vec2(cos(theta), sin(theta));
}

vec4 initPosition(int index) {
    const vec3 spawn = vec3(0);
    return vec4(spawn, calculateLifetime(index));
}

vec4 initVelocity(int index) {
    return vec4(calculateInitialVelocity(index), 0, 0);
}

vec4 updatePosition(int index) {
    // TODO [Task 16]
    // - sample prevPos and prevVel at uv
    pos.xyz = texture(prevPos, uv).xyz + texture(prevVel, uv).xyz * dt;
    // - xyz: pos + vel * dt
    // - w component is lifetime, so keep it from the previous position
    pos.w = texture(prevPos, uv).w;
    return pos;
}

vec4 updateVelocity(int index) {
    const float G = -0.1;
    const float B = 1.0;
    // TODO [Task 16]
    // - sample prevVel at uv
    // - One force is gravity in y direction.  Add G * dt.
    vel.y = texture(prevVel, uv).y + G * dt;
    vel.x = texture(prevVel, uv).x;
    vel.z = texture(prevVel, uv).z;
    // - Second force is linear drag in -v direction.
    vel.y += -vel.y*B*dt;
    vel.x += -vel.x*B*dt;
    vel.z += -vel.z*B*dt;
    // - w component is age, so add dt
    vel.w = texture(prevVel, uv).w + dt;
    return vel;
}

void main() {
    int index = int(uv.x * numParticles);
    //To initialize explosion, reset firstPass
    if (firstPass > 0.5) {
        pos = initPosition(index);
        vel = initVelocity(index);
    } else {
        pos = updatePosition(index);
        vel = updateVelocity(index);
        //If Particle Dies (Currently resets the position and velocity)
        if (pos.w < vel.w) {
            //pos = initPosition(index);
            //vel = initVelocity(index);
            //discard;
        }
    }
}
