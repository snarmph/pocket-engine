#ifndef MATMATH_HPP
#define MATMATH_HPP
#include <cmath>
#include "mat.hpp"
#include "vec.hpp"

namespace math {
    /*-+-+-+-
	  mat2
	+-+-+-+*/

    // scale m by s
    void scale(mat2 &m, vec2f &s);
    void scale(mat2 &m, float s);

    void rotate(mat2 &m, float angle);

    /*-+-+-+-
	  mat3
	+-+-+-+*/

    // translate m by t
    void translate(mat3 &m, vec3f &t);

    // scale m by s
    void scale(mat3 &m, vec2f &s);
    void scale(mat3 &m, float s);

    // create viewport with width and height
    void viewport(mat3 &m, float width, float height);

    /*-+-+-+-
	  mat4
	+-+-+-+*/

    void orthographic(mat4 &m, float right, float left, float top, float bottom, float near, float far);

} // namespace math

#endif