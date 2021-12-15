#version 330 core

uniform float firstPass;
uniform sampler2D prevPos;
uniform sampler2D prevVel;
uniform int numParticles;
uniform float dt;
uniform float B;
uniform vec3 spawnPoint;
uniform int numLayers;
uniform float GMultiplier;
uniform float time;

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
float hash(float n) {
    return fract(sin(n)*75.5453123);
}

// Helper functions to procedurally generate lifetimes and initial velocities
// based on particle index
float calculateLifetime(int index) {
    const float MAX_LIFETIME = 2.0;
    const float MIN_LIFETIME = 1.5;
    return MIN_LIFETIME + (MAX_LIFETIME - MIN_LIFETIME) * hash(index * 2349.2693 + time);
}

float calculateTrailLifetime(int index) {
    const float MAX_TRAIL_LIFETIME = 0.25;
    const float MIN_TRAIL_LIFETIME = 0.1;
    return MIN_TRAIL_LIFETIME + (MAX_TRAIL_LIFETIME - MIN_TRAIL_LIFETIME) * hash(index * 2349.2693 + time);
}

vec3 calculateInitialVelocity(int index) {
    float theta = 2*PI * hash(index * 8.0238 + time);
    float phi = PI * hash(index * 7.0123 + time);
    //float theta = index;
    const float MIN_VEL = 1;
    float velMag = MIN_VEL + 0.1 * hash(index * 98723.345 + time);
    return velMag * vec3(sin(phi)*cos(theta), sin(phi)*sin(theta), cos(phi));
}

vec4 initPosition(int index) {
    return vec4(spawnPoint, calculateLifetime(index));
}

vec4 initTrailPosition(int index) {
    return vec4(spawnPoint, calculateTrailLifetime(index));
}

vec4 reinitTrailPosition(int index){
    float newindex = float(index%numParticles);
    pos.xyz = texture(prevPos, vec2(newindex/(numParticles*numLayers), uv.y)).xyz;
    pos.w = pos.w + calculateTrailLifetime(index);
    return pos;
}

vec4 initVelocity(int index) {
    return vec4(calculateInitialVelocity(index), 0);
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

vec4 updateTrailPosition(int index) {
    pos = texture(prevPos, uv);
    return pos;
}

vec4 updateVelocity(int index) {
    const float G = -0.2;
    // TODO [Task 16]
    // - sample prevVel at uv
    // - One force is gravity in y direction.  Add G * dt.
    vel.x = texture(prevVel, uv).x;
    vel.y = texture(prevVel, uv).y + G * GMultiplier * dt;
    vel.z = texture(prevVel, uv).z;
    // - Second force is linear drag in -v direction.
    vel.x += -vel.x*B*dt;
    vel.y += -vel.y*B*dt;
    vel.z += -vel.z*B*dt;
    // - w component is age, so add dt
    vel.w = texture(prevVel, uv).w + dt;
    return vel;
}

vec4 updateTrailVelocity(int index) {
    // - w component is age, so add dt
    vel.xyz = texture(prevVel, uv).xyz;
    vel.w = texture(prevVel, uv).w + dt;
    return vel;
}

void main() {
    int index = int(uv.x * numParticles * numLayers);
    if(index < numParticles){
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
    } else{
        if (firstPass > 0.5) {
            pos = initTrailPosition(index);
            vel = vec4(0, 0, 0, 0);
        } else {
            pos = updateTrailPosition(index);
            vel = updateTrailVelocity(index);
            //If Particle Dies (Currently resets the position and velocity)
            if (pos.w < vel.w) {
                pos = reinitTrailPosition(index);
                vel = vec4(0, 0, 0, vel.w);
                //discard;
            }
            if (pos.w > 2.25){
                //discard;
            }
        }
    }
}
