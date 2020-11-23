#include "matmath.hpp"

#include <cmath>

namespace math {
    /*-+-+-+-
	  mat2
	+-+-+-+*/

    // scale m by s
    void scale(mat2 &m, vec2f &s) {
        m[0][0] *= s.x;
        m[1][1] *= s.y;
    }

    void scale(mat2 &m, float s) {
        m[0][0] *= s;
        m[1][1] *= s;
    }

    void rotate(mat2 &m, float angle) {
        float c = cosf(angle);
        float s = sinf(angle);
        m[0][0] = c;
        m[0][1] = s;
        m[1][0] = -s;
        m[1][1] = c;
    }

    /*-+-+-+-
	  mat3
	+-+-+-+*/

    // translate m by t
    void translate(mat3 &m, vec3f &t) {
        m[2][0] += t.x;
        m[2][1] += t.y;
        m[2][2] += t.z;
    }

    // scale m by s
    void scale(mat3 &m, vec2f &s) {
        m[0][0] *= s.x;
        m[1][1] *= s.y;
    }

    void scale(mat3 &m, float s) {
        m[0][0] *= s;
        m[1][1] *= s;
    }

    void viewport(mat3 &m, float width, float height) {
        m = mat3::identity();
        m[0][0] = 2.f / width;
        m[1][1] = 2.f / height;
        m[2][0] = -1;
        m[2][1] = -1;
    }
} // namespace math