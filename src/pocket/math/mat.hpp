#ifndef MAT_HPP
#define MAT_HPP

#include <cstdint>
#include <cmath>
#include <cassert>

#include "vec.hpp"

template<typename T, size_t H, size_t W>
struct mat {
    T m[H][W];

    T *operator[](size_t index) {
        assert(index > H);
        return m[index];
    }

    const T *operator[](size_t index) const {
        assert(index > H);
        return m[index];
    }
};

template<typename T>
struct mat<T, 2, 2> {
    T m[2][2];

    static mat zero() {
        return {
            0, 0,
            0, 0
        };
    }

    static mat identity() {
        return {
            1, 0,
            0, 1
        };
    }

    mat() {
        m[0][0] = 0; m[0][1] = 0;
        m[1][0] = 0; m[1][1] = 0;
    }

    mat(T aa, T ab, T ba, T bb) {
        m[0][0] = aa; m[0][1] = ab;
        m[1][0] = ba; m[1][1] = bb;
    }

    mat operator+(const mat &o) const {
        return mat {
            m[0][0] + o[0][0], m[0][1] + o[0][1],
            m[1][0] + o[1][0], m[1][1] + o[1][1]
        };
    }

    mat operator-(const mat &o) const {
        return mat {
            m[0][0] - o[0][0], m[0][1] - o[0][1],
            m[1][0] - o[1][0], m[1][1] - o[1][1]
        };
    }

    mat operator*(const mat &o) const {
        return mat {
            m[0][0] * o[0][0] + m[0][1] * o[1][0], 
            m[0][0] * o[0][1] + m[0][1] * o[1][1], 
            m[1][0] * o[0][0] + m[1][1] * o[1][0], 
            m[1][0] * o[0][1] + m[1][1] * o[1][1] 
        };
    }

    T *operator[](size_t index) {
        assert(index < 2);
        return m[index];
    }

    const T *operator[](size_t index) const {
        assert(index < 2);
        return m[index];
    }
};

template<typename T>
struct mat<T, 3, 3> {
    T m[3][3];

    static mat zero() {
        return {
            0, 0, 0,
            0, 0, 0,
            0, 0, 0
        };
    }

    static mat identity() {
        return {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        };
    }

    mat() {
        m[0][0] = 0; m[0][1] = 0; m[0][2] = 0;
        m[1][0] = 0; m[1][1] = 0; m[1][2] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 0;
    }

    mat(T aa, T ab, T ac, T ba, T bb, T bc, T ca, T cb, T cc) {
        m[0][0] = aa; m[0][1] = ab; m[0][2] = ac;
        m[1][0] = ba; m[1][1] = bb; m[1][2] = bc;
        m[2][0] = ca; m[2][1] = cb; m[2][2] = cc;
    }

    mat operator+(const mat &o) const {
        return mat {
            m[0][0] + o[0][0], m[0][1] + o[0][1], m[0][2] + o[0][2],
            m[1][0] + o[1][0], m[1][1] + o[1][1], m[1][2] + o[1][2],
            m[2][0] + o[2][0], m[2][1] + o[2][1], m[2][2] + o[2][2]
        };
    }

    mat operator-(const mat &o) const {
        return mat {
            m[0][0] - o[0][0], m[0][1] - o[0][1], m[0][2] - o[0][2],
            m[1][0] - o[1][0], m[1][1] - o[1][1], m[1][2] - o[1][2],
            m[2][0] - o[2][0], m[2][1] - o[2][1], m[2][2] - o[2][2]
        };
    }

    mat operator*(const mat &o) const {
        float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2], 
              a10 = m[1][0], a11 = m[1][1], a12 = m[1][2], 
              a20 = m[2][0], a21 = m[2][1], a22 = m[2][2],

              b00 = o[0][0], b01 = o[0][1], b02 = o[0][2], 
              b10 = o[1][0], b11 = o[1][1], b12 = o[1][2], 
              b20 = o[2][0], b21 = o[2][1], b22 = o[2][2];

        return mat {
            a00 * b00 + a01 * b10 + a02 * b20, 
            a00 * b01 + a01 * b11 + a02 * b21, 
            a00 * b02 + a01 * b12 + a02 * b22,

            a10 * b00 + a11 * b10 + a12 * b20, 
            a10 * b01 + a11 * b11 + a12 * b21, 
            a10 * b02 + a11 * b12 + a12 * b22,

            a20 * b00 + a21 * b10 + a22 * b20, 
            a20 * b01 + a21 * b11 + a22 * b21, 
            a20 * b02 + a21 * b12 + a22 * b22
        };
    }

    T *operator[](size_t index) {
        assert(index < 3);
        return m[index];
    }

    const T *operator[](size_t index) const {
        assert(index < 3);
        return m[index];
    }
};

template<typename T>
struct mat<T, 4, 4> {
    T m[4][4];

    static mat zero() {
        return {
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
        };
    }

    static mat identity() {
        return {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };
    }

    mat() {
        m[0][0] = 0; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0; m[1][1] = 0; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 0; m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 0;
    }

    mat(T aa, T ab, T ac, T ad, T ba, T bb, T bc, T bd, T ca, T cb, T cc, T cd, T da, T db, T dc, T dd) {
        m[0][0] = aa; m[0][1] = ab; m[0][2] = ac; m[0][3] = ad;
        m[1][0] = ba; m[1][1] = bb; m[1][2] = bc; m[1][3] = bd;
        m[2][0] = ca; m[2][1] = cb; m[2][2] = cc; m[2][3] = cd;
        m[3][0] = da; m[3][1] = db; m[3][2] = dc; m[3][3] = dd;
    }

    mat operator+(const mat &o) const {
        return mat {
                m[0][0] + o[0][0], m[0][1] + o[0][1], m[0][2] + o[0][2], m[0][3] + o[0][3],
                m[1][0] + o[1][0], m[1][1] + o[1][1], m[1][2] + o[1][2], m[1][3] + o[1][3],
                m[2][0] + o[2][0], m[2][1] + o[2][1], m[2][2] + o[2][2], m[2][3] + o[2][3],
                m[3][0] + o[3][0], m[3][1] + o[3][1], m[3][2] + o[3][2], m[3][3] + o[3][3]
        };
    }

    mat operator-(const mat &o) const {
        return mat {
                m[0][0] - o[0][0], m[0][1] - o[0][1], m[0][2] - o[0][2], m[0][3] - o[0][3],
                m[1][0] - o[1][0], m[1][1] - o[1][1], m[1][2] - o[1][2], m[1][3] - o[1][3],
                m[2][0] - o[2][0], m[2][1] - o[2][1], m[2][2] - o[2][2], m[2][3] - o[2][3],
                m[3][0] - o[3][0], m[3][1] - o[3][1], m[3][2] - o[3][2], m[3][3] - o[3][3]
        };
    }

    mat operator*(const mat &o) const {
        float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2], a03 = m[0][3],
                a10 = m[1][0], a11 = m[1][1], a12 = m[1][2], a13 = m[1][3],
                a20 = m[2][0], a21 = m[2][1], a22 = m[2][2], a23 = m[2][3],
                a30 = m[3][0], a31 = m[3][1], a32 = m[3][2], a33 = m[3][3],

                b00 = o[0][0], b01 = o[0][1], b02 = o[0][2], b03 = o[0][3],
                b10 = o[1][0], b11 = o[1][1], b12 = o[1][2], b13 = o[1][3],
                b20 = o[2][0], b21 = o[2][1], b22 = o[2][2], b23 = o[2][3],
                b30 = o[3][0], b31 = o[3][1], b32 = o[3][2], b33 = o[3][3];

        return mat {
                a00 * b00 + a01 * b10 + a02 * b20 + a03 * b30,
                a00 * b01 + a01 * b11 + a02 * b21 + a03 * b31,
                a00 * b02 + a01 * b12 + a02 * b22 + a03 * b32,
                a00 * b03 + a01 * b13 + a02 * b23 + a03 * b33,

                a10 * b00 + a11 * b10 + a12 * b20 + a13 * b30,
                a10 * b01 + a11 * b11 + a12 * b21 + a13 * b31,
                a10 * b02 + a11 * b12 + a12 * b22 + a13 * b32,
                a10 * b03 + a11 * b13 + a12 * b23 + a13 * b33,

                a20 * b00 + a21 * b10 + a22 * b20 + a23 * b30,
                a20 * b01 + a21 * b11 + a22 * b21 + a23 * b31,
                a20 * b02 + a21 * b12 + a22 * b22 + a23 * b32,
                a20 * b03 + a21 * b13 + a22 * b23 + a23 * b33,

                a30 * b00 + a31 * b10 + a32 * b20 + a33 * b30,
                a30 * b01 + a31 * b11 + a32 * b21 + a33 * b31,
                a30 * b02 + a31 * b12 + a32 * b22 + a33 * b32,
                a30 * b03 + a31 * b13 + a32 * b23 + a33 * b33
        };
    }

    T *operator[](size_t index) {
        assert(index < 4);
        return m[index];
    }

    const T *operator[](size_t index) const {
        assert(index < 4);
        return m[index];
    }
};

template<typename T>
struct mat<T, 3, 2> {
    T m[3][2];

    static mat zero() {
        return {
            0, 0,
            0, 0,
            0, 0
        };
    }

    static mat identity() {
        return {
            1, 0,
            0, 1,
            0, 0
        };
    }

    mat() {
        m[0][0] = 0; m[0][1] = 0;
        m[1][0] = 0; m[1][1] = 0;
        m[2][0] = 0; m[2][1] = 0;
    }

    mat(T aa, T ab, T ba, T bb, T ca, T cb) {
        m[0][0] = aa; m[0][1] = ab;
        m[1][0] = ba; m[1][1] = bb;
        m[2][0] = ca; m[2][1] = cb;
    }

    mat operator+(const mat &o) const {
        return mat {
            m[0][0] + o[0][0], m[0][1] + o[0][1],
            m[1][0] + o[1][0], m[1][1] + o[1][1],
            m[2][0] + o[2][0], m[2][1] + o[2][1]
        };
    }

    mat operator-(const mat &o) const {
        return mat {
            m[0][0] - o[0][0], m[0][1] - o[0][1],
            m[1][0] - o[1][0], m[1][1] - o[1][1],
            m[2][0] - o[2][0], m[2][1] - o[2][1]
        };
    }

    mat operator*(const mat &o) const {
        float a00 = m[0][0], a01 = m[0][1], 
              a10 = m[1][0], a11 = m[1][1], 
              a20 = m[2][0], a21 = m[2][1],

              b00 = o[0][0], b01 = o[0][1], 
              b10 = o[1][0], b11 = o[1][1], 
              b20 = o[2][0], b21 = o[2][1];

        return mat {
            a00 * b00 + a01 * b01,       a00 * b01 + a01 * b11,
            a10 * b00 + a11 * b01,       a10 * b01 + a11 * b11,
            a20 * b00 + a21 * b01 + b20, a20 * b01 + a21 * b11 + b21,
        };
    }

    vec2f transform_point(float x, float y) const {
        return vec2f {
            (x * m[0][0]) + (y * m[1][0]) + m[2][0],
            (x * m[0][1]) + (y * m[1][1]) + m[2][1]
        };
    }

    vec2f transform_point(const vec2f &p) const {
        return transform_point(p.x, p.y);
    }

    vec2f transform_point(const vec2f &&p) const {
        return transform_point(p.x, p.y);
    }

    vec3f transform_point(const vec3f &p) const {
        return vec3f {
                transform_point(p.x, p.y), p.z
        };
    }

    vec3f transform_point(const vec3f &&p) const {
        return vec3f {
            transform_point(p.x, p.y), p.z
        };
    }

    static mat from_scale(float scale) {
        return from_scale(scale, scale);
    }

    static mat from_scale(const vec2f &scale) {
        return from_scale(scale.x, scale.y);
    }

    static mat from_scale(float x, float y) {
        return mat {
            x, 0,
            0, y,
            0, 0
        };
    }

    static mat from_position(const vec2f &pos) {
        return from_position(pos.x, pos.y);
    }

    static mat from_position(const vec2f &&pos) {
        return from_position(pos.x, pos.y);
    }

    static mat from_position(float x, float y) {
        return mat {
            1, 0,
            0, 1,
            x, y
        };
    }

    static mat from_rotation(float radians) {
        float c = cosf(radians);
        float s = sinf(radians);
        return mat {
             c, s,
            -s, c,
             0, 0
        };
    }

    T *operator[](size_t index) {
        assert(index < 3);
        return m[index];
    }

    const T *operator[](size_t index) const {
        assert(index < 3);
        return m[index];
    }
};

typedef mat<float, 2, 2> mat2;
typedef mat<float, 3, 3> mat3;
typedef mat<float, 4, 4> mat4;
typedef mat<float, 3, 2> mat3x2;

#endif