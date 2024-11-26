#pragma once
#include "Query.hpp"
#include "Relation.hpp"
#include "Operator.hpp"

class InsertTo : public Query{
public:
    bool executeQuery(const std::shared_ptr<DataBase> &) const override = 0;
};
