#pragma once
#include "Condition.hpp"
class ConditionAnd : Condition {
public:
    ConditionAnd(const std::shared_ptr<Condition>&, const std::shared_ptr<Condition>&);
    std::shared_ptr<Table> execute(const std::shared_ptr<Table> &) override;
    ~ConditionAnd() override = default;
private:
    std::shared_ptr<Condition> m_leftCondition;
    std::shared_ptr<Condition> m_rightCondition;
};
