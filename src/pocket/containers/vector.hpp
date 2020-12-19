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
#ifndef NDEBUG
        bool freed = false;
#endif

        explicit vector(size_t initial_allocation = 1) {
            _data = (T *) malloc(sizeof(T) * initial_allocation);
            assert(_data && "coudln't allocate data in constructor");
            _allocated = initial_allocation;
        }

        ~vector() {
            for(size_t i=0; i<_size; i++)
                _data[i].~T();
            free(_data);
#ifndef NDEBUG
            freed = true;
#endif
        }

        void deep_copy(const vector<T> &other) {
            reserve(other._size);
            for(size_t i=0; i<other._size; i++)
                push_back(other._data[i]);
            _size = other._size;
        }

        T *data() {
            return _data;
        }

        size_t allocated() const {
            return _allocated;
        }

        size_t size() const {
            return _size;
        }

        void reallocate(size_t newsize) {
            T *tmp = (T *) realloc(_data, sizeof(T) * newsize);
            assert(tmp && "couldn't allocate data in resize");
            _data = tmp;
            _allocated = newsize;
        }

        void reserve(size_t newsize) {
            if(_allocated - _size < newsize)
                reallocate(_allocated + newsize);
        }

        void resize(size_t newsize) {
            printf("newsize %lu, old %lu\n", newsize, _size);
            // if you need to add data, emplace it back
            if(newsize > _size) {
                for(size_t i=_size; i<newsize; i++)
                    emplace_back();
            }
            // otherwise, just reallocate the data
            else {
                for(size_t i=_size-1; i>=newsize; i--) {
                    _data[i].~T();
                    printf("deleting : %lu\n", i);
                }
                reallocate(newsize);
            }
        }

        void resize(size_t newsize, T &values) {
            if(newsize <= _allocated) {
            }
            else {
            }
        }

        void push_back(T &value) {
            _data[_size++] = value;
            if(_size == _allocated)
                reallocate(_allocated * 2);
        }

        void push_back(T &&value) {
            emplace_back(value);
        }

        template<typename ... Ts>
        void emplace_back(Ts... args) {
            new(&_data[_size++]) T(args...);
            if(_size == _allocated)
                reallocate(_allocated * 2);
        }

        T pop() {
            assert(_size > 0);
            T value = _data[--_size];
            _data[_size].~T();
            return value;
        }

        void erase(size_t position) {
            assert(position < _size && "accessing position too high for erase");
            _data[position].~T();
            if(position != --_size)
                _data[position] = _data[_size];
        }

        void clear() {
             for(size_t i=0; i<_size; i++)
                 _data[i].~T();
            _size = 0;
        }

        void dispose() {
            this->~vector();
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

        const T *begin() const {
            return &_data[0];
        }

        const T *end() const {
            return &_data[_size];
        }

        T &front() {
            return *(begin());
        }

        T &back() {
            assert(size() > 0 && "back is front");
            return *(end()-1);
        }

        bool empty() {
            return _size == 0;
        }

    };
} // mem

#endif // VECTOR_HPP