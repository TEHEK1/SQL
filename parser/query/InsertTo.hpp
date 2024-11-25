#pragma once
#include <Query.hpp>
#include <Relation.hpp>
#include <Condition.hpp>

class InsertTo : public Query, public Relation{
public:
    InsertTo(const std::shared_ptr<SeList>&, const std::shared_ptr<Relation>&, const std::shared_ptr<Condition>&);
    std::shared_ptr<Table> execute(const std::shared_ptr<DataBase> &) const override;
private:
};
