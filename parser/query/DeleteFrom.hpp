#pragma once
#include <Query.hpp>
#include <Relation.hpp>
#include <Condition.hpp>

class DeleteFrom : public Query, public Relation {
public:
    DeleteFrom(const Relation &, const Condition &);
};
