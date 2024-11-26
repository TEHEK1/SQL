#include "ColumnMeta.hpp"
#include <stdexcept>

ColumnMeta::ColumnMeta(long long realColumnNum, ObjectTypes type, std::unordered_set<Attributes> attributes = {}, int lastValue = -1, int sizeValue = 0)
    : realColumnNum(realColumnNum), type(type), attributes(attributes), lastValue(lastValue), sizeValue(sizeValue) {
    setDefaultValue(type);
}

ColumnMeta::ColumnMeta(const ColumnMeta& other, long long realColumnNum)
    : realColumnNum(realColumnNum), type(other.type), attributes(other.attributes), lastValue(other.lastValue), sizeValue(other.sizeValue) {
    setDefaultValue(other.type);
}

std::shared_ptr<Object> ColumnMeta::getNextIncrement() {
    if(type != ObjectTypes::INT32) {
        throw std::runtime_error("wrong type in getNextIncrement");
    }
    return std::make_shared<Object>(ObjectTypes::INT32, lastValue + 1);
}

std::shared_ptr<Object> ColumnMeta::updateNextIncrement() {
    if(type != ObjectTypes::INT32) {
        throw std::runtime_error("wrong type in updateNextIncrement");
    }
    lastValue += 1;
    return std::make_shared<Object>(ObjectTypes::INT32, lastValue);
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
    return std::make_shared<Object>(defaultValue);
}

void ColumnMeta::setDefaultValue(ObjectTypes objectTypes) {
    using variant = std::variant<int32_t, bool, std::string, std::vector<bool>>;
    switch (objectTypes)
    {
    case ObjectTypes::BOOL :
        defaultValue = Object(ObjectTypes::INT32,variant ((bool)false));
        break;
    case ObjectTypes::BYTES :
        defaultValue = Object(ObjectTypes::INT32,variant ((std::vector<bool>)std::vector<bool>(sizeValue)));
        break;
    case ObjectTypes::INT32 :
        defaultValue = Object(ObjectTypes::INT32,variant ((int32_t)0));
        break;
    case ObjectTypes::STRING :
        std::string spaces(sizeValue, ' ');
        defaultValue = Object(ObjectTypes::STRING,variant(spaces));
        break;
    }
}