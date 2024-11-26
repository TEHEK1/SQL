#pragma once
#include "Condition.hpp"
#include "Tokenizer.h"

class ConditionMathExpression : public Condition{
public:
    ConditionMathExpression(const std::shared_ptr<Operator> &, const std::shared_ptr<Operator> &, TokenType);
    std::shared_ptr<Table> getTableCondition(const std::shared_ptr<Table> &) const override;
    std::shared_ptr<Object> getObjectOperator(const std::shared_ptr<Row> &, const TableMeta &) const override;
    ~ConditionMathExpression() override = default;
private:
    std::shared_ptr<Operator> m_operator1;
    std::shared_ptr<Operator> m_operator2;
    TokenType m_tokenType;
};
