#include <memory>
#include <Row.hpp>

std::shared_ptr<Object> Row::getFields(int index) {
    return fields[index];
}