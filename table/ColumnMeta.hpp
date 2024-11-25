#pragma once
#include <memory>
#include "Index.hpp"
#include "Object.hpp"
#include "OrderedIndex.hpp"
#include "UnorderedIndex.hpp"
#include <unordered_set>
#include "Attributes.hpp"

class ColumnMeta {
public:
    ColumnMeta(long long realColumnNum, ObjectTypes type, std::unordered_set<Attributes> attributes = {}, int lastValue = -1, int sizeValue = 0);

    long long getNextIncrement(); // retuns next if int
    bool canInsert(std::shared_ptr<Object> object) const; // Checks can we insert object to this column according to its attributes and type
    long long getRealColumnNum() const; // returns saved columnNum;
    bool updateInsert(std::shared_ptr<Object> value); // update Meta information like object is inserted to table in this column
    ObjectTypes getType() const; // returns type
    std::shared_ptr<OrderedIndex> getOrderedIndex(); // returns shared_ptr to Ordered Index if exists, else null shared_ptr
    std::shared_ptr<UnorderedIndex> getUnorderedIndex();// returns shared_ptr to Unordered Index if exists, else null shared_ptr
private:
    void setDefaultValue(ObjectTypes objectTypes);
    std::unordered_set<Attributes> attributes;
    long long lastValue = -1; // if the object type is not a number then store -1
    ObjectTypes type;
    std::shared_ptr<OrderedIndex> ordered;
    std::shared_ptr<UnorderedIndex> unordered;
    long long realColumnNum;
    Object defaultValue;
    long long sizeValue = 0;
};
