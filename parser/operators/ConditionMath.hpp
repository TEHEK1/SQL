#pragma once
#include "Condition.hpp"
#include "Operator.hpp"
#include "Tokenizer.h"

class ConditionMath : public Condition {
public:
    ConditionMath(const std::shared_ptr<Condition> &, const std::shared_ptr<Condition> &, TokenType);
    ConditionMath(const std::shared_ptr<Operator> &, const std::shared_ptr<Operator> &, TokenType);
};
