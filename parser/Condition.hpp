#pragma once
#include "Operator.hpp"
#include "Table.hpp"

class Condition : public Operator {
public:
    [[nodiscard]] virtual std::shared_ptr<Table> execute (const std::shared_ptr<Table> &) const = 0;
    std::shared_ptr<Object> execute(const std::shared_ptr<Row> &, const TableMeta &) override = 0;
    ~Condition() override = default;
};
