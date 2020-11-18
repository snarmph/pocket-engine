#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <new>

namespace mem {
    template<typename T>
    struct vector {
        T *_data = nullptr;
        size_t _allocated = 0;
        size_t _size = 0;

        vector(size_t initial_allocation = 1) {
            _data = (T *) malloc(sizeof(T) * initial_allocation);
            assert(_data && "coudln't allocate data in constructor");
            _allocated = initial_allocation;
        }
        ~vector() {
            for(size_t i=0; i<_size; i++)
                _data[i].~T();
            free(_data);
        }

        T *data() {
            return _data;
        }

        size_t allocated() {
            return _allocated;
        }

        size_t size() {
            return _size;
        }

        void reserve(size_t newsize) {
            resize(_allocated + newsize);
        }

        void resize(size_t newsize) {
            //printf("resizing from %lu to %lu\n", _allocated, newsize);
            _data = (T *) realloc(_data, sizeof(T) * newsize);
            assert(_data && "couldn't allocate data in resize");
            _allocated = newsize;
        }

        void push_back(T &value) {
            _data[_size++] = value;
            if(_size == _allocated)
                resize(_allocated * 2);
        }

        void push_back(T &&value) {
            emplace_back(value);
        }

        template<typename ... Ts>
        void emplace_back(Ts... args) {
            new(&_data[_size++]) T(args...);
            if(_size == _allocated)
                resize(_allocated * 2);
        }

        void erase(size_t position) {
            assert(position < _size && "accessing position too high for erase");
            _data[position].~T();
            if(position != --_size)
                _data[position] = _data[_size];
        }

        T &operator[](size_t position) {
            assert(position < _size && "accessing position too high");
            return _data[position];
        }

        T *begin() {
            return &_data[0];
        }

        T *end() {
            return &_data[_size];
        }

    };
} // mem



#endif // VECTOR_HPP