#pragma once
#include "Condition.hpp"
#include "Operator.hpp"
#include "Tokenizer.h"

class ConditionMathLogical : public Condition {
public:
    ConditionMathLogical(const std::shared_ptr<Condition> &, const std::shared_ptr<Condition> &, TokenType);
    std::shared_ptr<Table> getTableCondition(const std::shared_ptr<Table> &) const override;
    std::shared_ptr<Object> getObjectOperator(const std::shared_ptr<Row> &, const TableMeta &) const override;
    ~ConditionMathLogical() override = default;
private:
    std::shared_ptr<Condition> m_condition1;
    std::shared_ptr<Condition> m_condition2;
    TokenType m_tokenType;
};
