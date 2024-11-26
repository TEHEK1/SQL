#pragma once
#include "Operator.hpp"
#include "Tokenizer.h"
class OperatorMath: public Operator {
public:
    OperatorMath(const std::shared_ptr<Operator> & operator1, const std::shared_ptr<Operator> &operator2, TokenType);
    std::shared_ptr<Object> getObjectOperator(const std::shared_ptr<Row> &, const TableMeta &) const override;
    ObjectTypes getTypeOperator(const TableMeta &) const override;
    ~OperatorMath() override =default;
private:
    std::shared_ptr<Operator> m_operator1;
    std::shared_ptr<Operator> m_operator2;
    TokenType m_tokenType;
};
