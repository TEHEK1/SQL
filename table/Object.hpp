#pragma once
#include "ObjectTypes.h"
#include <variant>
#include <string>
#include <vector>

class Object {
public:
    Object(ObjectTypes type, std::variant<int32_t, bool, std::string, std::vector<bool>> value) : type(type), value(value) {}

    template <typename T>
    T getValue() const {
        if constexpr (std::is_same_v<T, int32_t>) {
            return std::get(value);
        } else if constexpr (std::is_same_v<T, bool>) {
            return std::get(value);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return std::get(value);
        } else if constexpr (std::is_same_v<T, std::vector<bool>>) {
            return std::get(value);
        } else {
            throw std::runtime_error("Invalid type requested");
        }
    }

private:
    ObjectTypes type;
    std::variant<int32_t, bool, std::string, std::vector<bool>> value;
};