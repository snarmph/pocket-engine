#pragma once

#include <unordered_map>
#include <tuple>
//#include <string>
#include <array>
//#include <vector>
#include <queue>

#include "vector.hpp"
#include "string.hpp"

template<typename T, typename Q>
using map = std::unordered_map<T, Q>;

using std::pair;
using mem::string;
using std::array;
using mem::vector;
using std::queue;

//using bitvector = std::vector<bool>;
using bitvector = mem::vector<bool>;

//template<typename T, typename Q>
//using pair = std::pair<T, Q>;

//using string = std::string;

//template<typename T, size_t N>
//using array = std::array<T, N>;
//
//template<typename T>
//using vector = mem::vector<T>;