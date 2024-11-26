#include "Object.hpp"

bool Object::operator==(const Object& other) const {
    return (other.type == type && other.value == value);
}