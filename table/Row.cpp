#include <memory>
#include <Row.hpp>

std::shared_ptr<Object> Row::getField(long long index) {
    return fields[index];
}