#include "vecmath.hpp"
#include <math.h>


namespace math {

/*-+-+-+-
  vec2f
+-+-+-+*/

    float dot(const vec2f &v1, const vec2f &v2) {
        return ((v1.x * v2.x) + (v1.y * v2.y));
    }

    void normalize(vec2f &dest) {
        float magnitude = mag(dest);
        if (magnitude)
            dest *= 1.f / magnitude;
    }

    vec2f normalized(const vec2f &v) {
        vec2f norm = v;
        normalize(norm);
        return norm;
    }


    float mag(const vec2f &v) {
        return sqrtf((v.x * v.x) + (v.y * v.y));
    }

    float mag2(const vec2f &v) {
        return ((v.x * v.x) + (v.y * v.y));
    }


    bool are_equals(const vec2f &v1, const vec2f &v2, float epsilon) {
        return (
                (fabsf(v1.x - v2.x) < epsilon) &&
                (fabsf(v1.y - v2.y) < epsilon)
        );
    }

/*-+-+-+-
  vec3f
+-+-+-+*/

    float dot(const vec3f &v1, const vec3f &v2) {
        return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
    }

    vec3f cross(const vec3f &v1, const vec3f &v2) {
        return {
                (v1.y * v2.z) - (v1.z * v2.y),
                (v1.z * v2.x) - (v1.x * v2.z),
                (v1.x * v2.y) - (v1.y * v2.x)
        };
    }


    void normalize(vec3f &dest) {
        float magnitude = mag(dest);
        if (magnitude)
            dest *= 1.f / magnitude;
    }

    vec3f normalized(const vec3f &v) {
        vec3f norm = v;
        normalize(norm);
        return norm;
    }


    float mag(const vec3f &v) {
        return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    }

    float mag2(const vec3f &v) {
        return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    }


    bool are_equals(const vec3f &v1, const vec3f &v2, float epsilon) {
        return (
                (fabsf(v1.x - v2.x) < epsilon) &&
                (fabsf(v1.y - v2.y) < epsilon) &&
                (fabsf(v1.z - v2.z) < epsilon)
        );
    }
} // namespace math
