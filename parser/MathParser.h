#ifndef MATHPARSER_HPP
#define MATHPARSER_HPP

#include <memory>
#include <string>
#include <stdexcept>
#include <variant>
#include "Tokenizer.h"
#include "Condition.hpp"
#include "ConditionMath.hpp"
#include "ConditionObject.hpp"
#include "Operator.hpp"
#include "OperatorIdentifier.hpp"
#include "OperatorMath.hpp"
#include "OperatorObject.hpp"
#include "Object.hpp"
#include "ObjectTypes.hpp"

// Класс для обертки Condition и Operator в одном объекте
struct Expression {
    std::shared_ptr<Condition> my_condition = nullptr;
    std::shared_ptr<Operator> my_operator = nullptr;

    explicit Expression(const std::shared_ptr<Condition> &_my_condition) : my_condition(_my_condition) {};
    explicit Expression(const std::shared_ptr<Operator> &_my_operator) : my_operator(_my_operator) {};
    explicit Expression(const std::string &identifier) :
        my_condition(std::make_shared<ConditionObject>(std::make_shared<Object>(ObjectTypes::BOOL, identifier == "true"))),
        my_operator(std::make_shared<OperatorIdentifier>(identifier))
    {};

    template<class T>
    T get() {
        if constexpr (std::is_same_v<T, std::shared_ptr<Condition>>) {
            return my_condition;
        } else if constexpr (std::is_same_v<T, std::shared_ptr<Operator>>) {
            return my_operator;
        }
        throw std::runtime_error("Unexpected type in Expression getter");
    }
};

// Основной парсер для математики и условий
class MathParser {
public:
    explicit MathParser(Tokenizer tokenizer);

    std::shared_ptr<Condition> parse();

private:
    std::shared_ptr<Condition> parseCondition();
    std::shared_ptr<Expression> parseExpression();  // Используем Expression для обработки как Condition, так и Operator
    std::shared_ptr<Operator> parseOperator();
    std::shared_ptr<Operator> parseTerm();
    std::shared_ptr<Operator> parseFactor();

    Tokenizer tokenizer;
    Token currentToken;
};

#endif // MATHPARSER_HPP
