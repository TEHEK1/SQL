#include "ColumnMeta.hpp"


ColumnMeta::ColumnMeta(long long realColumnNum, ObjectTypes type, std::unordered_set<Attributes> attributes = {}, int lastValue = -1, int sizeValue = 0)
    : realColumnNum(realColumnNum), type(type), attributes(attributes), lastValue(lastValue), sizeValue(sizeValue) {
    setDefaultValue(type);
}

long long ColumnMeta::getNextIncrement() {
    if(lastValue >= 0) {
        return lastValue + 1;
    }
    return lastValue;
}

bool ColumnMeta::canInsert(std::shared_ptr<Object> object) const {
    return (object -> getType() == type);
}

long long ColumnMeta::getRealColumnNum() const {
    return realColumnNum;
}

bool ColumnMeta::updateInsert(std::shared_ptr<Object> value) {
    if(lastValue >= 0) {
        lastValue += 1;
    }
    // тут будет обновление индексов
    return true;
}

ObjectTypes ColumnMeta::getType() const {
    return type;
}

std::shared_ptr<OrderedIndex> ColumnMeta::getOrderedIndex() {
    return ordered;
}   

std::shared_ptr<UnorderedIndex> ColumnMeta::getUnorderedIndex() {
    return unordered;
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