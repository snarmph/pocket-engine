#ifndef VECMATH_HPP
#define VECMATH_HPP
#include "vec.hpp"

namespace math {
	template<typename T>
	constexpr T max(T a, T b) {
		return (a>b) ? a : b;
	}

	template<typename T>
	constexpr T min(T a, T b) {
		return (a<b) ? a : b;
	}

	template<typename T>
	constexpr T clamp(T value, T _max, T _min) {
		return min(max(value, _min), _max);
	}

	/*-+-+-+-
	  vec2f
	+-+-+-+*/

	float dot(const vec2f &v1, const vec2f &v2);

	void normalize(vec2f &dest);
	vec2f normalized(const vec2f &v);

	float mag(const vec2f &v);
	float mag2(const vec2f &v);

	bool are_equals(const vec2f &v1, const vec2f &v2, float epsilon);

	/*-+-+-+-
	  vec3f
	+-+-+-+*/

	float dot(const vec3f &v1, const vec3f &v2);
	vec3f cross(const vec3f &v1, const vec3f &v2);

	void normalize(vec3f &dest);
	vec3f normalized(const vec3f &v);

	float mag(const vec3f &v);
	float mag2(const vec3f &v);

	bool are_equals(const vec3f &v1, const vec3f &v2, float epsilon);

} // namespace math

#endif