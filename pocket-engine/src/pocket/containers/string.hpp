#pragma once

#include <cstdlib>
#include <cassert>

#include <iostream>
#include <xhash>
#include <string>
#include <initializer_list>

namespace mem {
	struct string {
        char *buf = nullptr;
        size_t alloc = 0;
        size_t sz = 0;

        string();
        ~string();

        string(const string &other);
        string(const std::initializer_list<char> &list);
        string(const char *cstr);
        string(const std::string &stdstr);

        template<typename T>
        string(const T &other) = delete;

        string &assing(const char *cstr);
        string &copy(const string &other);

        string substr(const size_t from, const size_t to);

        const char *cstr();
        const std::string stdstr()  const;
        char *data();
        const char *data() const;
        size_t allocated() const;
        size_t size() const;

        void reallocate(size_t newsize);
        void reserve(size_t newsize);
        void resize(size_t newsize);

        void push_back(char &value);
        void push_back(char &&value);

        char pop();

        void erase(size_t position);

        inline void remove(char &instance);

        void clear();
        void dispose();

        string &operator=(const char *cstr);
        string &operator=(const string &other);
        string &operator+=(const char &c);
        string operator+(const char &c);
        string &operator+=(const char *cstr);
        string operator+(const char *cstr);
        string &operator+=(const string &other);
        string operator+(const string &other);
        char &operator[](size_t position);
        const char &operator[](size_t position) const;
        bool operator==(const string &other) const;

        char *begin();
        char *end();
        const char *begin() const;
        const char *end() const;
        char &front();
        char &back();

        bool empty() const;

        void emplace_back(char c = '\0') {
            buf[sz++] = c;
            if (sz == alloc)
                reallocate(alloc * 2);
        }
	};

    std::ostream &operator<<(std::ostream &os, const string &str);

} // namespace mem 

namespace std {
    template<>
    struct hash<mem::string> {
        size_t operator()(const mem::string &str) const {
            // should probably not do this
            return std::_Hash_array_representation(str.buf, str.size());
        }
    };
}
