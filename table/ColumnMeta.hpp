#pragma once
#include <memory>
#include "Index.hpp"
#include "Object.hpp"
#include "OrderedIndex.hpp"
#include "UnorderedIndex.hpp"

class ColumnMeta {
public:
    ColumnMeta(long long realColumnNum);
    ColumnMeta(const ColumnMeta&, long long realColumnNum);
    long long getNextIncrement(); // retuns next
    bool canInsert(const Object& object) const; // Checks can we insert object to this column according to its attributes and type
    long long getRealColumnNum() const; // returns saved columnNum;
    bool updateInsert(std::shared_ptr<Object>); // update Meta information like object is inserted to table in this column
    getType() const; // returns type
    std::shared_ptr<OrderedIndex> getOrderedIndex(); // returns shared_ptr to Ordered Index if exists, else null shared_ptr
    std::shared_ptr<UnorderedIndex> getUnorderedIndex();// returns shared_ptr to Unordered Index if exists, else null shared_ptr
};
