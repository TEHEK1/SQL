#pragma once
#include <memory>
#include "JoinEqualList.hpp"
#include "Relation.hpp"

class RelationJoin : public Relation{
public:
    RelationJoin(const std::shared_ptr<Relation>&, const std::shared_ptr<Relation>&, const std::shared_ptr<JoinEqualList>&);
    std::shared_ptr<Table> getTableRelation(const std::shared_ptr<DataBase> &) const override;
    std::string getName() const override;
private:
    std::shared_ptr<Relation> m_relation1;
    std::shared_ptr<Relation> m_relation2;
    std::shared_ptr<JoinEqualList> m_joinEqualList;
};
