#pragma once
#include "Condition.hpp"
class ConditionAnd : Condition {
public:
    ConditionAnd(const Condition&, const Condition&);
    Table execute(const Table &) override;
    ~ConditionAnd() override = default;
};
