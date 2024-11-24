#pragma once
#include "Condition.hpp"
#include "Operator.hpp"
class ConditionLess : Condition {
public:
    ConditionLess(const Operator&, const Operator&);
    Table execute(const Table &) override;
    ~ConditionLess() override = default;
};
