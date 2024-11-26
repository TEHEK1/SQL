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
    ColumnMeta(const ColumnMeta&, long long realColumnNum);
    std::shared_ptr<Object> getNextIncrement() const; // retuns next if int

    long long getRealColumnNum() const; // returns saved columnNum;
    bool canInsert(std::shared_ptr<Object> object) const; // Checks can we insert object to this column according to its attributes and type
    bool canDelete(const std::shared_ptr<Object>& object) const; // Checks can we insert object to this column according to its attributes and type
    bool canUpdate(const std::shared_ptr<Object>& , const std::shared_ptr<Object>&) const; // Checks can we insert object to this column according to its attributes and type
    ObjectTypes getType() const; // returns type
    std::shared_ptr<OrderedIndex> getOrderedIndex() const; // returns shared_ptr to Ordered Index if exists, else null shared_ptr
    std::shared_ptr<UnorderedIndex> getUnorderedIndex() const;// returns shared_ptr to Unordered Index if exists, else null shared_ptr
    std::shared_ptr<Object> getDefaultValue() const;
    bool hasAutoIncrement() const;
    bool hasDefaultValue() const;
private:
    friend class TableFactory;
    bool updateInsert(std::shared_ptr<Object> value, std::shared_ptr<Row>); // update Meta information like object is inserted to table in this column
    bool updateDelete(const std::shared_ptr<Object>& value); // update Meta information like object is inserted to table in this column
    bool updateUpdate(std::shared_ptr<Object> value, std::shared_ptr<Object> object, std::shared_ptr<Row>); // update Meta information like object is inserted to table in this column
    void setDefaultValue(ObjectTypes objectTypes);
    std::shared_ptr<Object> updateNextIncrement(); // retuns next if int
    std::unordered_set<Attributes> attributes;
    long long lastValue = -1; // if the object type is not a number then store -1
    ObjectTypes type;
    std::shared_ptr<OrderedIndex> ordered;
    std::shared_ptr<UnorderedIndex> unordered;
    long long realColumnNum;
    Object defaultValue;
    long long sizeValue = 0;
};
