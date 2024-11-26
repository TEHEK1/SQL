#pragma once
#include "ObjectTypes.hpp"
#include <variant>
#include <string>
#include <vector>

class Object {
public:
    Object(ObjectTypes type, std::variant<int32_t, bool, std::string, std::vector<bool>> value) : type(type), value(value) {}
    Object(const Object &other) : type(other.type), value(other.value) {};

    bool operator==(const Object& other) const;
    bool operator<(const Object& other) const;
    bool operator>(const Object& other) const;

    template <typename T>
    Object(ObjectTypes type, T value) : type(type), value(value) {}
    
    Object() {
        type = ObjectTypes::INT32;
        value = 0;
    }

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