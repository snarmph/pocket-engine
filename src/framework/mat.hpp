#ifndef MAT_HPP
#define MAT_HPP

#include <cstdint>
#include <cmath>
#include <cassert>

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
    using cur_mat = mat<T, 2, 2>;
    T m[2][2];

    static cur_mat zero() {
        return {
            0, 0,
            0, 0
        };
    }

    static cur_mat identity() {
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

    cur_mat operator+(const cur_mat &o) {
        return cur_mat {
            m[0][0] + o[0][0], m[0][1] + o[0][1],
            m[1][0] + o[1][0], m[1][1] + o[1][1]
        };
    }

    cur_mat operator-(const cur_mat &o) {
        return cur_mat {
            m[0][0] - o[0][0], m[0][1] - o[0][1],
            m[1][0] - o[1][0], m[1][1] - o[1][1]
        };
    }

    cur_mat operator*(const cur_mat &o) {
        return cur_mat {
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
    using cur_mat = mat<T, 3, 3>;
    T m[3][3];

    static cur_mat zero() {
        return {
            0, 0, 0,
            0, 0, 0,
            0, 0, 0
        };
    }

    static cur_mat identity() {
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

    cur_mat operator+(const cur_mat &o) {
        return cur_mat {
            m[0][0] + o[0][0], m[0][1] + o[0][1], m[0][2] + o[0][2],
            m[1][0] + o[1][0], m[1][1] + o[1][1], m[1][2] + o[1][2],
            m[2][0] + o[2][0], m[2][1] + o[2][1], m[2][2] + o[2][2]
        };
    }

    cur_mat operator-(const cur_mat &o) {
        return cur_mat {
            m[0][0] - o[0][0], m[0][1] - o[0][1], m[0][2] - o[0][2],
            m[1][0] - o[1][0], m[1][1] - o[1][1], m[1][2] - o[1][2],
            m[2][0] - o[2][0], m[2][1] - o[2][1], m[2][2] - o[2][2]
        };
    }

    cur_mat operator*(const cur_mat &o) {
        float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2], 
              a10 = m[1][0], a11 = m[1][1], a12 = m[1][2], 
              a20 = m[2][0], a21 = m[2][1], a22 = m[2][2],

              b00 = o[0][0], b01 = o[0][1], b02 = o[0][2], 
              b10 = o[1][0], b11 = o[1][1], b12 = o[1][2], 
              b20 = o[2][0], b21 = o[2][1], b22 = o[2][2];

        return cur_mat {
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

typedef mat<float, 2, 2> mat2;
typedef mat<float, 3, 3> mat3;

#endif