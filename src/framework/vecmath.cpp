#include "vecmath.hpp"
#include <math.h>

float math::to_rad(const float deg) {
	return deg * math::PI / 180.f;
}

/*-+-+-+-
  vec2f
+-+-+-+*/

float math::dot(const vec2f &v1, const vec2f &v2) {
	return ((v1.x * v2.x) + (v1.y * v2.y));
}

void math::normalize(vec2f &dest) {
	float mag = math::mag(dest);
	if (mag)
		dest *= 1.f / mag;
}

vec2f math::normalized(const vec2f &v) {
	vec2f norm = v;
	math::normalize(norm);
	return norm;
}


float math::mag(const vec2f &v) {
	return sqrtf((v.x * v.x) + (v.y * v.y));
}

float math::mag2(const vec2f &v) {
	return ((v.x * v.x) + (v.y * v.y));
}


bool math::are_equals(const vec2f &v1, const vec2f &v2, float epsilon) {
	return (
		(fabsf(v1.x - v2.x) < epsilon) &&
		(fabsf(v1.y - v2.y) < epsilon)
	);
}

/*-+-+-+-
  vec3f
+-+-+-+*/

float math::dot(const vec3f &v1, const vec3f &v2) {
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

vec3f math::cross(const vec3f &v1, const vec3f &v2) {
	return {
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x)
	};
}


void math::normalize(vec3f &dest) {
	float mag = math::mag(dest);
	if (mag)
		dest *= 1.f / mag;
}

vec3f math::normalized(const vec3f &v) {
	vec3f norm = v;
	math::normalize(norm);
	return norm;
}


float math::mag(const vec3f &v) {
	return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

float math::mag2(const vec3f &v) {
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}


bool math::are_equals(const vec3f &v1, const vec3f &v2, float epsilon) {
	return (
		(fabsf(v1.x - v2.x) < epsilon) &&
		(fabsf(v1.y - v2.y) < epsilon) &&
		(fabsf(v1.z - v2.z) < epsilon)
	);
}