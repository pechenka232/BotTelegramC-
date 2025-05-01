#include "json_utils.h"

namespace JsonUtils {
    std::string jsonToString(const nlohmann::json& jsonData) {
        return jsonData.dump(4);  // Pretty printing with indent of 4 spaces
    }
}
