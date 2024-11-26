#include "ColumnMeta.hpp"
#include <stdexcept>

ColumnMeta::ColumnMeta(long long realColumnNum, ObjectTypes type, std::unordered_set<Attributes> attributes, int lastValue, int sizeValue, std::shared_ptr<Object> defaultValue)
    : realColumnNum(realColumnNum), type(type), attributes(attributes), lastValue(lastValue), sizeValue(sizeValue) {
    setDefaultValue(defaultValue);
}

ColumnMeta::ColumnMeta(const ColumnMeta& other, long long realColumnNum)
    : realColumnNum(realColumnNum), type(other.type), attributes(other.attributes), lastValue(other.lastValue), sizeValue(other.sizeValue) {
    setDefaultValue(other.defaultValue);
}

std::shared_ptr<Object> ColumnMeta::getNextIncrement() const {
    if(type != ObjectTypes::INT32) {
        throw std::runtime_error("wrong type in getNextIncrement");
    }
    return std::make_shared<Object>(ObjectTypes::INT32, static_cast<int32_t>(lastValue + 1));
}

std::shared_ptr<Object> ColumnMeta::updateNextIncrement() {
    if(type != ObjectTypes::INT32) {
        throw std::runtime_error("wrong type in updateNextIncrement");
    }
    lastValue += 1;
    return std::make_shared<Object>(ObjectTypes::INT32, static_cast<int32_t>(lastValue));
}

long long ColumnMeta::getRealColumnNum() const {
    return realColumnNum;
}

bool ColumnMeta::canInsert(std::shared_ptr<Object> object) const {
    return (object -> getType() == type);
}

bool ColumnMeta::updateInsert(std::shared_ptr<Object> value, std::shared_ptr<Row>) {
    
    if(!canInsert(value)) {
        return false;
    }
    if(lastValue >= 0) {
        lastValue += 1;
    }
    // тут будет обновление индексов
    return true;
}

bool ColumnMeta::canDelete(const std::shared_ptr<Object>& object) const {
    return (object -> getType() == type);
}

bool ColumnMeta::updateDelete(const std::shared_ptr<Object>& value) {
    if(!canInsert(value)) {
        return false;
    }
    if(lastValue >= 0) {
        lastValue -= 1;
    }
    // тут будет обновление индексов
    return true;
}

bool ColumnMeta::canUpdate(const std::shared_ptr<Object>& value , const std::shared_ptr<Object>& object) const {
    return value -> getType() == object -> getType() && object -> getType() == type;
}
bool ColumnMeta::updateUpdate(std::shared_ptr<Object> value, std::shared_ptr<Object> object, std::shared_ptr<Row> row) {
    if(!canUpdate(value, object)) {
        return false;
    }
    //обновление индексов
    return true;
}

ObjectTypes ColumnMeta::getType() const {
    return type;
}

std::shared_ptr<OrderedIndex> ColumnMeta::getOrderedIndex() const {
    return ordered;
}   

std::shared_ptr<UnorderedIndex> ColumnMeta::getUnorderedIndex() const {
    return unordered;
}

std::shared_ptr<Object> ColumnMeta::getDefaultValue() const {
    return defaultValue;
}

bool ColumnMeta::hasAutoIncrement() const {
    if(!(type == ObjectTypes::INT32)) {
        return false;
    }
    return true;
}

bool ColumnMeta::hasDefaultValue() const {
    return defaultValue != nullptr;
}

void ColumnMeta::setDefaultValue(std::shared_ptr<Object> object) {
    if(object != 0) {
    defaultValue = std::move(object);
    }
}