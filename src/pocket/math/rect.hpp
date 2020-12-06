#ifndef POCKET_ENGINE_RECT_HPP
#define POCKET_ENGINE_RECT_HPP

#include <pocket/types.hpp>
#include "vec.hpp"

template<typename T>
struct rect {
    union {
        T data[4];
        struct {
            T x, y, w, h;
        };
    };

    rect();
    rect(T _x, T _y, T _w, T _h);
    rect(vec<T, 2> &pos, vec<T, 2> &size);
    rect(vec<T, 2> &&pos, vec<T, 2> &&size);

    vec<T, 2> position() const {
        return {x, y};
    }
    vec<T, 2> size() const {
        return {w, h};
    }

    void scale(T s);
    void scale(T sx, T sy);

    void inflate(T amount);

    vec<T, 2> center() const;
    T center_x() const;
    T center_y() const;

    bool contains(const vec<T, 2> &point) const;
    bool intersects(const rect &other) const;

    bool operator==(const rect &other) const;
    bool operator!=(const rect &other) const;

    rect operator+(const vec<T, 2> &other) const;
    rect operator-(const vec<T, 2> &other) const;
    rect &operator+=(const vec<T, 2> &other) const;
    rect &operator-=(const vec<T, 2> &other) const;
};

typedef rect<int>    recti;
typedef rect<float>  rectf;
typedef rect<double> rectd;

template<typename T>
rect<T>::rect() {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

template<typename T>
rect<T>::rect(T _x, T _y, T _w, T _h) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

template<typename T>
rect<T>::rect(vec<T, 2> &pos, vec<T, 2> &size) {
    x = pos.x;
    y = pos.y;
    w = size.x;
    h = size.y;
}

template<typename T>
rect<T>::rect(vec<T, 2> &&pos, vec<T, 2> &&size) {
    x = pos.x;
    y = pos.y;
    w = size.x;
    h = size.y;
}

template<typename T>
void rect<T>::scale(T s) {
    x *= s;
    y *= s;
    w *= s;
    h *= s;
}

template<typename T>
void rect<T>::scale(T sx, T sy) {
    x *= sx;
    y *= sy;
    w *= sx;
    h *= sy;
}

template<typename T>
void rect<T>::inflate(T amount) {
    x -= amount;
    y -= amount;
    w += amount * 2;
    h += amount * 2;
}

template<typename T>
vec<T, 2> rect<T>::center() const {
    return vec<T, 2>(x+(w/2), y+(h/2));
}

template<typename T>
T rect<T>::center_x() const {
    return x+(w/2);
}

template<typename T>
T rect<T>::center_y() const {
    return y+(h/2);
}

template<typename T>
bool rect<T>::contains(const vec<T, 2> &point) const {
    return (
            point.x >= x && point.x < x + w &&
            point.y >= y && point.y < y + h
    );
}

template<typename T>
bool rect<T>::intersects(const rect &other) const {
    return (
            x + w >= other.x &&
            y + h >= other.y &&
            x < other.x + other.w &&
            y < other.y + other.h
    );
}

template<typename T>
bool rect<T>::operator==(const rect &other) const {
    return (
            x == other.x && y == other.y &&
            w == other.w && h == other.h
    );
}

template<typename T>
bool rect<T>::operator!=(const rect &other) const {
    return (
            x != other.x || y != other.y ||
            w != other.w || h != other.h
    );
}

template<typename T>
rect<T> rect<T>::operator+(const vec<T, 2> &other) const {
    return rect(
            x + other.x, y + other.y, w, h
    );
}

template<typename T>
rect<T> rect<T>::operator-(const vec<T, 2> &other) const {
    return rect(
            x - other.x, y - other.y, w, h
    );
}

template<typename T>
rect<T> &rect<T>::operator+=(const vec<T, 2> &other) const {
    x += other.x;
    y += other.y;
    return *this;
}

template<typename T>
rect<T> &rect<T>::operator-=(const vec<T, 2> &other) const {
    x -= other.x;
    y -= other.y;
    return *this;
}


#endif //POCKET_ENGINE_RECT_HPP
