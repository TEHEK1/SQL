#pragma once
#include "Query.hpp"
#include "UpdateEqualList.hpp"
#include "Relation.hpp"
#include "Condition.hpp"
class UpdateFromWhere : public Query {
public:
    UpdateFromWhere(const UpdateList&, const std::shared_ptr<Relation>&,
            const std::shared_ptr<Condition>& );
    bool executeQuery(const std::shared_ptr<DataBase> &) const override;
    ~UpdateFromWhere() override =default;
private:
    UpdateList m_updateList;
    std::shared_ptr<Relation> m_relation;
    std::shared_ptr<Condition> m_condition;
};
