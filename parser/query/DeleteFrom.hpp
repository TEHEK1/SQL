#pragma once
#include <Query.hpp>
#include <Relation.hpp>
#include <Condition.hpp>

class DeleteFrom : public Query {
public:
    DeleteFrom(const std::shared_ptr<Relation> &, const std::shared_ptr<Condition> &);
    bool executeQuery(const std::shared_ptr<DataBase> &) const override;
    ~DeleteFrom() override =default;
private:
    std::shared_ptr<Relation> m_relation;
    std::shared_ptr<Condition> m_condition;
};
