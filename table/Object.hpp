#pragma once
#include "ObjectTypes.hpp"
#include <variant>
#include <string>
#include <vector>

class Object {
public:
    Object(ObjectTypes type, std::variant<int32_t, bool, std::string, std::vector<bool>> value) : type(type), value(value) {}

    template <typename T>
    T getValue() const {
        return std::get<T>(value);
    }

    ObjectTypes getType() {
        return type;
    }    

private:
    ObjectTypes type;
    std::variant<int32_t, bool, std::string, std::vector<bool>> value;
};