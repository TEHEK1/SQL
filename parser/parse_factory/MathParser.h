#ifndef MATHPARSER_HPP
#define MATHPARSER_HPP

#include <memory>
#include <string>
#include <stdexcept>
#include <variant>
#include "Tokenizer.h"
#include "Condition.hpp"
#include "ConditionMathLogical.hpp"
#include "ConditionObject.hpp"
#include "Operator.hpp"
#include "OperatorIdentifier.hpp"
#include "OperatorMath.hpp"
#include "OperatorObject.hpp"
#include "Object.hpp"
#include "ObjectTypes.hpp"

struct Expression {
    std::shared_ptr<Condition> my_condition = nullptr;
    std::shared_ptr<Operator> my_operator = nullptr;
    explicit Expression(const std::shared_ptr<Condition> &_my_condition);
    explicit Expression(const std::shared_ptr<Operator> &_my_operator);
    explicit Expression(const std::string &identifier);
    template<class T> T get();
};

// Основной парсер для математики и условий
class MathParser {
public:
    explicit MathParser(Tokenizer tokenizer);

    std::shared_ptr<Condition> parse();

private:
    std::shared_ptr<Condition> parseCondition();
    std::shared_ptr<Expression> parseExpression();  // Используем Expression для обработки как Condition, так и Operator
    std::shared_ptr<Expression> parseTerm();
    std::shared_ptr<Expression> parseFactor();

    Tokenizer tokenizer;
    Token currentToken;
};

#endif // MATHPARSER_HPP
