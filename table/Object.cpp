#include "Object.hpp"
#include <stdexcept>

bool Object::operator==(const Object& other) const {
    return (other.type == type && other.value == value);
}

bool Object::operator<(const Object& other) const {
    if(other.type != type) {
        throw std::runtime_error("несравнимые типы");
    }
    return other.value > value;
}

bool Object::operator>(const Object& other) const {
    if(other.type != type) {
        throw std::runtime_error("несравнимые типы");
    }
    return other.value < value;
}