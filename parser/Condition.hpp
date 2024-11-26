#pragma once
#include "Operator.hpp"
#include "Table.hpp"

class Condition : public Operator {
public:
    virtual std::shared_ptr<Table> getTableCondition (const std::shared_ptr<Table> &) const = 0;
    std::shared_ptr<Object> getObjectOperator(const std::shared_ptr<Row> &, const TableMeta &) const override = 0;
    ~Condition() override = default;
protected:
    virtual std::shared_ptr<Table> getTableConditionLinear(const std::shared_ptr<Table> &) const;
};
