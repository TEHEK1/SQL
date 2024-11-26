#include <memory>
#include "Object.hpp"
#include "ObjectTypes.hpp"
#include <stdexcept>
#include <variant>
#include <string>
#include <unordered_map>

#include "Condition.hpp"
#include "ConditionMath.hpp"
#include "ConditionObject.hpp"
#include "Operator.hpp"
#include "OperatorIdentifier.hpp"
#include "OperatorMath.hpp"
#include "OperatorObject.hpp"
#include "Tokenizer.h"

struct Expression {
    std::shared_ptr<Condition> my_condition = nullptr;
    std::shared_ptr<Operator> my_operator = nullptr;
    explicit Expression(const std::shared_ptr<Condition> &_my_condition) : my_condition(_my_condition) {};
    explicit Expression(const std::shared_ptr<Operator> &_my_operator) : my_operator(_my_operator) {};
    explicit Expression(const std::string &identifier) :
        my_condition(std::make_shared<ConditionObject>(std::make_shared<Object>(ObjectTypes::BOOL, identifier == "true"))),
        my_operator(std::make_shared<OperatorIdentifier>(identifier))
    {};
    template<class T> T get() {
        if constexpr (std::is_same_v<T, std::shared_ptr<Condition>>) {
            return my_condition;
        } else if constexpr (std::is_same_v<T, std::shared_ptr<Operator>>) {
            return my_operator;
        }
        throw std::runtime_error("Unexpected type. in Expression getter");
    }
};

class MathParser {
public:
    explicit MathParser(Tokenizer tokenizer) : tokenizer(std::move(tokenizer)) {
        currentToken = this->tokenizer.next();
    }

    std::shared_ptr<Condition> parse() {
        auto condition = parseCondition();
        if (currentToken.type != TokenType::END) {
            throw std::runtime_error("Unexpected token after condition.");
        }
        return condition;
    }

private:
    std::shared_ptr<Condition> parseCondition() {
        auto left = parseExpression();
        if (currentToken.type == TokenType::EQUAL || currentToken.type == TokenType::NEQUAL ||
            currentToken.type == TokenType::LESS || currentToken.type == TokenType::GREATER ||
            currentToken.type == TokenType::LEQUAL || currentToken.type == TokenType::GEQUAL) {
            Token op = currentToken;
            currentToken = tokenizer.next();
            auto right = parseExpression();
            return std::make_shared<ConditionMath>(left->get<std::shared_ptr<Operator>>(), right->get<std::shared_ptr<Operator>>(), op.type); // создаем объект Condition
        } else if (currentToken.type == TokenType::AND || currentToken.type == TokenType::XOR || currentToken.type == TokenType::OR) {
            Token op = currentToken;
            currentToken = tokenizer.next();
            auto right = parseCondition();
            return std::make_shared<ConditionMath>(left->get<std::shared_ptr<Condition>>(), right, op.type); // создаем объект Condition
        } else {
            throw std::runtime_error("Expected condition operator.");
        }
    }

    std::shared_ptr<Expression> parseExpression() {
        auto left = parseTerm();  // Начинаем с терма
        while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
            Token op = currentToken;
            currentToken = tokenizer.next();
            auto right = parseTerm();
            left = std::make_shared<Expression>(std::dynamic_pointer_cast<Operator>(std::make_shared<OperatorMath>(left->get<std::shared_ptr<Operator>>(), right->get<std::shared_ptr<Operator>>(), op.type)));
        }
        return left;
    }

    std::shared_ptr<Expression> parseTerm() {
        auto left = parseFactor();  // Начинаем с фактора
        while (currentToken.type == TokenType::STAR || currentToken.type == TokenType::SLASH || currentToken.type == TokenType::MOD) {
            Token op = currentToken;
            currentToken = tokenizer.next();
            auto right = parseFactor();
            left = std::make_shared<Expression>(std::dynamic_pointer_cast<Operator>(std::make_shared<OperatorMath>(left->get<std::shared_ptr<Operator>>(), right->get<std::shared_ptr<Operator>>(), op.type)));  // Создаем оператор для умножения/деления
        }
        return left;
    }

    std::shared_ptr<Expression> parseFactor() {
        if (currentToken.type == TokenType::NUMBER) {
            int value = std::stoi(currentToken.value);
            currentToken = tokenizer.next();
            return std::make_shared<Expression>(std::make_shared<OperatorObject>(std::make_shared<Object>(ObjectTypes::INT32, value)));
        }
        if (currentToken.type == TokenType::STRING) {
            std::string value = currentToken.value;
            currentToken = tokenizer.next();
            return std::make_shared<Expression>(std::make_shared<OperatorIdentifier>(value));
        }
        if (currentToken.type == TokenType::TRUE || currentToken.type == TokenType::FALSE) {
            bool value = currentToken.type == TokenType::TRUE;
            currentToken = tokenizer.next();
            return std::make_shared<Expression>(std::make_shared<ConditionObject>(std::make_shared<Object>(ObjectTypes::BOOL, value)));
        }
        if (currentToken.type == TokenType::IDENTIFIER) {
            std::string identifier = currentToken.value;
            currentToken = tokenizer.next();
            return std::make_shared<Expression>(identifier);  // Пример для идентификатора
        }
        if (currentToken.type == TokenType::LPAREN) {
            currentToken = tokenizer.next();
            auto expr = parseExpression();  // Рекурсивно разбираем выражение в скобках
            if (currentToken.type != TokenType::RPAREN) {
                throw std::runtime_error("Expected closing parenthesis.");
            }
            currentToken = tokenizer.next();
            return expr;
        }
        throw std::runtime_error("Unexpected token.");
    }

    Tokenizer tokenizer;
    Token currentToken;
};
