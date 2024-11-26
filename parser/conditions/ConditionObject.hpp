#pragma once
#include "Condition.hpp"
#include "Object.hpp"

class ConditionObject : public Condition {
public:
    ConditionObject(const std::shared_ptr<Object>&);
    std::shared_ptr<Table> getTableCondition (const std::shared_ptr<Table> &) const override;
    std::shared_ptr<Object> getObjectOperator(const std::shared_ptr<Row> &, const TableMeta &) const override;
    ~ConditionObject() override = default;
private:
    std::shared_ptr<Object> m_object;
};
