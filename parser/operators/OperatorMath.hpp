#pragma once
#include "Operator.hpp"
#include "Tokenizer.h"
class OperatorMath: public Operator {
public:
    OperatorMath(const std::shared_ptr<Operator> &, const std::shared_ptr<Operator> &, TokenType);
};
