#pragma once
#include <string>
#include "Condition.hpp"
#include "Object.hpp"

class ConditionIdentifier : public Condition {
public:
    explicit ConditionIdentifier(const std::string&);
    std::shared_ptr<Table> getTableCondition(const std::shared_ptr<Table> &) const override;
    std::shared_ptr<Object> getObjectOperator(const std::shared_ptr<Row> &, const TableMeta &) const override;
    ~ConditionIdentifier() override = default;
private:
    std::string m_columnName;
};
