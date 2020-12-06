#pragma once
#include <map>
#include <vector>
#include <string>

namespace json {
    // forward declaration for json::Value
    class Value;

    using Object = std::map<std::string, json::Value>;
    using Array = std::vector<json::Value>;
    using Null = Value;
}