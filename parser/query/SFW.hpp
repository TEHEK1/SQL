#pragma once
#include <memory>
#include "Condition.hpp"
#include "SeList.hpp"
#include "Query.hpp"
#include "Relation.hpp"

class SFW : public Query, public Relation{
public:
    SFW(const std::shared_ptr<SeList>&, const std::shared_ptr<Relation>&, const std::shared_ptr<Condition>&);
    std::shared_ptr<Table> execute(const std::shared_ptr<DataBase> &) const override;
private:
    std::shared_ptr<SeList> m_seList;
    std::shared_ptr<Relation> m_relation;
    std::shared_ptr<Condition> m_condition;
};
