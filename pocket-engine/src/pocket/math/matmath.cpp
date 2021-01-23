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

    /*-+-+-+-
	  mat4
	+-+-+-+*/

    void orthographic(mat4 &m, float right, float left, float top, float bottom, float near, float far) {
        float rl, tb, fn;
        rl =  1.f / (right - left);
        tb =  1.f / (top   - bottom);
        fn = -1.f / (far   - near);

        m = mat4::zero();

        m[0][0] =  2.f * rl;
        m[1][1] =  2.f * tb;
        m[2][2] =  2.f * fn;
        m[3][0] = -(right  + left)   * rl;
        m[3][1] = -(top    + bottom) * tb;
        m[3][2] =  (far    + near)   * fn;
        m[3][3] =  1.f;
    }

} // namespace math