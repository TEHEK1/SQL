#pragma once
#include <map>
#include <memory>
#include <vector>
#include <Tokenizer.h>
#include <Condition.hpp>

// Узел бинарного выражения
class BinaryExpr : public Condition {
public:
    BinaryExpr(std::shared_ptr<Condition> left, Token op, std::shared_ptr<Condition> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    std::shared_ptr<Condition> left;
    Token op;
    std::shared_ptr<Condition> right;
};

// Узел унарного выражения
class UnaryExpr : public Condition {
public:
    UnaryExpr(Token op, std::shared_ptr<Condition> right)
        : op(op), right(std::move(right)) {}

    Token op;
    std::shared_ptr<Condition> right;
};

// Узел литерала (числа, строки)
class LiteralExpr : public Condition {
public:
    LiteralExpr(Token value) : value(value) {}

    Token value;
};

// Узел переменной (идентификатора)
class VariableExpr : public Condition {
public:
    VariableExpr(Token name) : name(name) {}

    Token name;
};

// Класс парсера
class MathParser {
public:
    explicit MathParser(Tokenizer tokenizer);

    // Начало парсинга выражения
    std::shared_ptr<Condition> parse();

private:
    // Функции парсинга
    std::shared_ptr<Condition> expression();
    std::shared_ptr<Condition> logical_or();
    std::shared_ptr<Condition> logical_and();
    std::shared_ptr<Condition> equality();
    std::shared_ptr<Condition> comparison();
    std::shared_ptr<Condition> term();
    std::shared_ptr<Condition> factor();
    std::shared_ptr<Condition> unary();
    std::shared_ptr<Condition> primary();

    // Управление токенами
    Token advance();
    Token peek();
    Token previous();
    bool match(TokenType type);
    bool check(TokenType type);

    Tokenizer tokenizer;
    Token currentToken;
    Token previousToken;
};