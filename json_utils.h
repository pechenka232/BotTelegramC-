#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <string>
#include <nlohmann/json.hpp>

namespace JsonUtils {
    std::string jsonToString(const nlohmann::json& jsonData);
}

#endif // JSON_UTILS_H
