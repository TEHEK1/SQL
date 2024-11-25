#pragma once
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include "Tokenizer.h"

// Базовый класс для всех узлов выражений
class Expr {
public:
    virtual ~Expr() = default;
};

// Узел бинарного выражения
class BinaryExpr : public Expr {
public:
    BinaryExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
};

// Узел унарного выражения
class UnaryExpr : public Expr {
public:
    UnaryExpr(Token op, std::shared_ptr<Expr> right)
        : op(op), right(std::move(right)) {}

    Token op;
    std::shared_ptr<Expr> right;
};

// Узел литерала (числа, строки)
class LiteralExpr : public Expr {
public:
    LiteralExpr(Token value) : value(value) {}

    Token value;
};

// Узел переменной (идентификатора)
class VariableExpr : public Expr {
public:
    VariableExpr(Token name) : name(name) {}

    Token name;
};

// Класс парсера
class MathParser {
public:
    explicit MathParser(Tokenizer tokenizer);

    // Начало парсинга выражения
    std::shared_ptr<Expr> parse();

private:
    // Функции парсинга
    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> logical_or();
    std::shared_ptr<Expr> logical_and();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> primary();

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

MathParser::MathParser(Tokenizer tokenizer)
    : tokenizer(std::move(tokenizer)) {
    advance(); // Инициализируем currentToken
}

Token MathParser::advance() {
    previousToken = currentToken;
    currentToken = tokenizer.next();
    return previousToken;
}

Token MathParser::peek() {
    return currentToken;
}

Token MathParser::previous() {
    return previousToken;
}

bool MathParser::check(TokenType type) {
    return currentToken.type == type;
}

bool MathParser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

// Парсинг выражения, начиная с логического ИЛИ
std::shared_ptr<Expr> MathParser::parse() {
    return expression();
}

std::shared_ptr<Expr> MathParser::expression() {
    return logical_or();
}

std::shared_ptr<Expr> MathParser::logical_or() {
    std::shared_ptr<Expr> expr = logical_and();

    while (match(TokenType::OR)) {
        Token op = previous();
        std::shared_ptr<Expr> right = logical_and();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::shared_ptr<Expr> MathParser::logical_and() {
    std::shared_ptr<Expr> expr = equality();

    while (match(TokenType::AND)) {
        Token op = previous();
        std::shared_ptr<Expr> right = equality();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::shared_ptr<Expr> MathParser::equality() {
    std::shared_ptr<Expr> expr = comparison();

    while (match(TokenType::EQUAL) || match(TokenType::NEQUAL)) {
        Token op = previous();
        std::shared_ptr<Expr> right = comparison();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::shared_ptr<Expr> MathParser::comparison() {
    std::shared_ptr<Expr> expr = term();

    while (match(TokenType::LESS) || match(TokenType::LEQUAL) ||
           match(TokenType::GREATER) || match(TokenType::GEQUAL)) {
        Token op = previous();
        std::shared_ptr<Expr> right = term();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::shared_ptr<Expr> MathParser::term() {
    std::shared_ptr<Expr> expr = factor();

    while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        Token op = previous();
        std::shared_ptr<Expr> right = factor();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::shared_ptr<Expr> MathParser::factor() {
    std::shared_ptr<Expr> expr = unary();

    while (match(TokenType::STAR) || match(TokenType::SLASH) || match(TokenType::MOD)) {
        Token op = previous();
        std::shared_ptr<Expr> right = unary();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::shared_ptr<Expr> MathParser::unary() {
    if (match(TokenType::NOT) || match(TokenType::MINUS)) {
        Token op = previous();
        std::shared_ptr<Expr> right = unary();
        return std::make_unique<UnaryExpr>(op, std::move(right));
    }
    return primary();
}

std::shared_ptr<Expr> MathParser::primary() {
    if (match(TokenType::NUMBER) || match(TokenType::STRING)) {
        return std::make_unique<LiteralExpr>(previous());
    }

    if (match(TokenType::IDENTIFIER)) {
        return std::make_unique<VariableExpr>(previous());
    }

    if (match(TokenType::LPAREN)) {
        std::shared_ptr<Expr> expr = expression();
        if (!match(TokenType::RPAREN)) {
            throw std::runtime_error("Expected ')'.");
        }
        return expr;
    }

    throw std::runtime_error("Expected expression.");
}
