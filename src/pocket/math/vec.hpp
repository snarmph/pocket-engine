#ifndef VEC_HPP
#define VEC_HPP

#include <cstdint>
#include <cmath>

template<typename T, size_t N>
struct vec {
    T v[N];

    vec<T, N>() {
        for (size_t i = 0; i < N; i++) {
            v[i] = 0;
        }
    }

    vec<T, N>(const vec<T, N> &other) {
        for (size_t i = 0; i < N; i++)
            v[i] = other.v[i];
    }

    vec<T, N>(T value_for_all) {
        for (size_t i = 0; i < N; i++)
            v[i] = value_for_all;
    }

    T& operator[](size_t index) {
        return v[index];
    }
    const T& operator[](size_t index) const {
        return v[index];
    }

    vec &operator=(const vec<T, N> &other) {
        for (size_t i = 0; i < N; i++)
            v[i] = other[i];
        return *this;
    }

    template<size_t N2>
    vec &operator=(const vec<T, N2> &other) {
        size_t s = (N > N2) ? N2 : N;
        for (size_t i = 0; i < s; i++)
            v[i] = other.v[i];
        return *this;
    }

    bool operator==(const vec<T, N> &other) {
        for (size_t i = 0; i < N; i++)
            if (v[i] != other[i])
                return false;
        return true;
    }
};

template<typename T>
struct vec<T, 2> {
    union {
        T v[2];
        struct {
            T x, y;
        };
    };

    vec<T, 2>() {
        x = y = 0;
    }

    vec<T, 2>(T value_for_all) {
        x = value_for_all;
        y = value_for_all;
    }

    vec<T, 2>(T _x, T _y) {
        x = _x;
        y = _y;
    }

    static vec one() {
        return { 1, 1 };
    }

    static vec zero() {
        return { 0, 0 };
    }

    bool operator==(const vec &other) {
        return (
            x == other.x && y == other.y
        );
    }

    vec &operator=(const vec &other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    vec operator-() {
        return vec {
            -x, -y
        };
    }

    vec operator+(const vec &other) {
        return vec {
            x + other.x, y + other.y
        };
    }

    vec operator-(const vec &other) {
        return vec {
            x - other.x, y - other.y
        };
    }

    vec operator*(const T &other) {
        return vec {
            x * other, y * other
        };
    }

    vec operator/(const T &other) {
        return vec {
            x / other, y / other
        };
    }

    void operator+=(const vec &other) {
        x += other.x;
        y += other.y;
    }

    void operator-=(const vec &other) {
        x -= other.x; 
        y -= other.y;
    }

    void operator*=(const float &other) {
        x *= other; 
        y *= other;
    }

    void operator/=(const float &other) {
        x /= other; 
        y /= other;
    }
};

template<typename T>
struct vec<T, 3> {
    union {
        T v[3];
        struct {
            T x, y, z;
        };
    };

    vec<T, 3>() {
        x = y = z = 0;
    }

    vec<T, 3>(T value_for_all) {
        x = value_for_all;
        y = value_for_all;
        z = value_for_all;
    }

    vec<T, 3>(T _x, T _y, T _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    vec<T, 3>(vec<T, 2> &other, T _z) {
        x = other.x;
        y = other.y;
        z = _z;
    }

    vec<T, 3>(vec<T, 2> &&other, T _z) {
        x = other.x;
        y = other.y;
        z = _z;
    }

    static vec one() {
        return { 1, 1, 1 };
    }

    static vec zero() {
        return { 0, 0, 0 };
    }

    bool operator==(const vec &other) {
        return (
            x == other.x && y == other.y && z == other.z
        );
    }

    vec &operator=(const vec &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    vec operator+(const vec &other) {
        return vec {
            x + other.x, y + other.y, z + other.z
        };
    }

    vec operator-(const vec &other) {
        return vec {
            x - other.x, y - other.y, z - other.z
        };
    }

    vec operator*(const T &other) {
        return vec {
            x * other, y * other, z * other
        };
    }

    vec operator/(const T &other) {
        return vec {
            x / other, y / other, z / other
        };
    }

    void operator+=(const vec &other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    void operator-=(const vec &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    void operator*=(const T &other) {
        x *= other;
        y *= other;
        z *= other;
    }

    void operator/=(const T &other) {
        x /= other;
        y /= other;
        z /= other;
    }
};

template<typename T>
struct vec<T, 4> {
    union {
        T v[4];
        struct {
            T x, y, z, w;
        };
    };

    vec<T, 4>() {
        x = y = z = w = 0;
    }

    vec<T, 4>(T value_for_all) {
        x = value_for_all;
        y = value_for_all;
        z = value_for_all;
        w = value_for_all;
    }

    vec<T, 4>(T _x, T _y, T _z, T _w) {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    vec<T, 4>(const vec<T, 2> &v1, const vec<T, 2> &v2) {
        x = v1.x;
        y = v1.y;
        z = v2.x;
        w = v2.y;
    }

    static vec one() {
        return { 1, 1, 1, 1 };
    }

    static vec zero() {
        return { 0, 0, 0, 0 };
    }

    bool operator==(const vec &other) {
        return (
            x == other.x && y == other.y && z == other.z && z == other.w
        );
    }

    vec &operator=(const vec &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
    }

    vec operator+(const vec &other) {
        return vec {
            x + other.x, y + other.y, z + other.z, w + other.w
        };
    }

    vec operator-(const vec &other) {
        return vec {
            x - other.x, y - other.y, z - other.z, w - other.w
        };
    }

    vec operator*(const T &other) {
        return vec {
            x * other, y * other, z * other, w * other
        };
    }

    vec operator/(const T &other) {
        return vec {
            x / other, y / other, z / other, w / other
        };
    }

    void operator+=(const vec &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
    }

    void operator-=(const vec &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
    }

    void operator*=(const T &other) {
        x *= other;
        y *= other;
        z *= other;
        w *= other;
    }

    void operator/=(const T &other) {
        x /= other;
        y /= other;
        z /= other;
        w /= other;
    }
};

typedef vec<int, 2>    vec2i;
typedef vec<float, 2>  vec2f;
typedef vec<double, 2> vec2d;

typedef vec<int, 3>    vec3i;
typedef vec<float, 3>  vec3f;
typedef vec<double, 3> vec3d;

typedef vec<int, 4>    vec4i;
typedef vec<float, 4>  vec4f;
typedef vec<double, 4> vec4d;

#endif // VEC_HPP