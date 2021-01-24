#include "string.hpp"

namespace mem {
    
    template <typename T>
    void copy_mem(T *dest, const T *src, const size_t sz) {
        for (size_t i = 0; i < sz; i++)
            dest[i] = src[i];
    }

    template <typename T>
    bool compare_mem(const T *buf1, const T *buf2, const size_t sz) {
        for (size_t i = 0; i < sz; i++)
            if (buf1[i] != buf2[i])
                return false;
        return true;
    }
    
    string::string() {
        buf = (char *)malloc(1);
        assert(buf && "coudln't allocate string in constructor");
        alloc = 1;
    }

    string::string(const string &other) {
        sz = other.sz;
        alloc = other.sz + 1;
        buf = (char *)malloc(alloc);
        assert(buf && "coudln't allocate string in constructor");
        copy_mem(buf, other.buf, sz);
    }

    string::string(const std::initializer_list<char> &list) {
        alloc = list.size() + 1;
        buf = (char *)malloc(alloc);
        assert(buf && "coudln't allocate data in constructor");

        for (auto &l : list)
            emplace_back(l);
    }

    string::string(const char *cstr) {
        size_t len = strlen(cstr);
        alloc = len + 1;
        buf = (char *)malloc(alloc);
        assert(buf && "coudln't allocate string in constructor");
        sz = len;

        for (size_t i = 0; i < len; i++)
            buf[i] = cstr[i];
    }

    string::string(const std::string &stdstr) {
        alloc = stdstr.size() + 1;
        buf = (char *)malloc(alloc);
        assert(buf && "coudln't allocate string in constructor");
        sz = stdstr.size();
        copy_mem(buf, stdstr.data(), sz);
    }

    string &string::operator=(const char *cstr) {
        return assing(cstr);
    }

    string &string::operator=(const string &other) {
        return copy(other);
    }

    string &string::operator+=(const char &c) {
        emplace_back(c);
        return *this;
    }

    string string::operator+(const char &c) {
        string res{ *this };
        res += c;
        return res;
    }

    string &string::operator+=(const char *cstr) {
        size_t len = strlen(cstr);
        reserve(len + 1);
        copy_mem(&buf[sz], cstr, len);
        sz += len;

        return *this;
    }

    string string::operator+(const char *cstr) {
        string res{ *this };
        res += cstr;
        return res;
    }

    string &string::operator+=(const string &other) {
        reserve(other.size() + 1);
        copy_mem(&buf[sz], other.buf, other.size());
        sz += other.size();
        return *this;
    }

    string string::operator+(const string &other) {
        string res{ *this };
        res += other;
        return res;
    }

    string &string::assing(const char *cstr) {
        clear();
        size_t len = strlen(cstr);
        reserve(len + 1);
        sz = len;
        copy_mem(buf, cstr, len);
        return *this;
    }

    string &string::copy(const string &other) {
        reserve(other.sz + 1);
        copy_mem(buf, other.buf, other.sz);
        sz = other.sz;
        return *this;
    }

    string string::substr(const size_t from, const size_t to) {
        assert(from >= 0 && "substring accessing less than 0");
        assert(to <= sz && "substring accessing more than string buffer");
        string out;
        size_t len = to - from;
        out.reserve(len + 1);
        copy_mem(out.buf, &buf[from], len);
        out.sz = len;
        return out;
    }

    const char *string::cstr() {
        if (back() != '\0')
            emplace_back('\0');
        return buf;
    }

    const std::string string::stdstr() const {
        return std::string(buf, sz);
    }

    string::~string() {
        assert(buf && "freeing unitialized string");
        free((void*) buf);
    }

    char *string::data() {
        return buf;
    }

    const char *string::data() const {
        return buf;
    }

    size_t string::allocated() const {
        return alloc;
    }

    size_t string::size() const {
        return sz;
    }

    void string::reallocate(size_t newsize) {
        char *tmp = (char *)realloc(buf, newsize);
        assert(tmp && "couldn't allocate data in resize");
        buf = tmp;
        alloc = newsize;
    }

    void string::reserve(size_t newsize) {
        if (alloc - sz < newsize)
            reallocate(alloc + newsize);
    }

    void string::resize(size_t newsize) {
        // if you need to add data, emplace it back
        if (newsize > sz) {
            for (size_t i = sz; i < newsize; i++)
                emplace_back();
        }
        // otherwise, just reallocate the data
        else {
            reallocate(newsize);
        }
    }

    void string::push_back(char &value) {
        emplace_back(value);
    }

    void string::push_back(char &&value) {
        emplace_back(value);
    }

    char string::pop() {
        assert(sz > 0);
        char value = buf[--sz];
        return value;
    }

    void string::erase(size_t position) {
        assert(position < sz && "accessing position too high for erase");
        if (position != --sz)
            buf[position] = buf[sz];
    }

    inline void string::remove(char &instance) {
        assert(instance && "erasing a nullptr");
        size_t position = 0;
        for (long i = (long)(sz)-1; i >= 0; i--) {
            if (buf[i] == instance) {
                position = i;
                erase(i);
                return;
            }
        }
        assert(false && "couldn't find instance in array");
    }

    void string::clear() {
        sz = 0;
    }

    void string::dispose() {
        this->~string();
    }

    char &string::operator[](size_t position) {
        assert(position < sz && "accessing position too high");
        return buf[position];
    }

    const char &string::operator[](size_t position) const {
        assert(position < sz && "accessing position too high");
        return buf[position];
    }

    char *string::begin() {
        return &buf[0];
    }

    char *string::end() {
        return &buf[sz];
    }

    const char *string::begin() const {
        return &buf[0];
    }

    const char *string::end() const {
        return &buf[sz];
    }

    char &string::front() {
        return *(begin());
    }

    char &string::back() {
        assert(sz > 0 && "back is front");
        return *(end() - 1);
    }

    bool string::empty() const {
        return sz == 0;
    }

    bool string::operator==(const string &other) const {
        if (buf == other.buf)
            return true;
        if (sz != other.sz)
            return false;
        return compare_mem(buf, other.buf, sz);
    }

    std::ostream &operator<<(std::ostream &os, const string &str) {
        os.write(str.buf, str.sz);
        return os;
    }

} // namespace mem 