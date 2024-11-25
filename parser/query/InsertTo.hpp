#pragma once
#include "Query.hpp"
#include "Relation.hpp"
#include "Operator.hpp"

class InsertTo : public Query{
public:
    bool execute(const std::shared_ptr<DataBase> &) const override = 0;
};
