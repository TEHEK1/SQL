#include "Tokenizer.h"
#include <string>
#include <stdexcept>
#include <cctype>

Tokenizer::Tokenizer(const std::string& str) : input(str), pos(0) {}

Token Tokenizer::next() {
    skipWhitespace();
    if (pos >= input.length()) {
        return Token{TokenType::END, ""};
    }

    // Multi-character operators
    if (match("!=")) {
        return Token{TokenType::NEQUAL, "!="};
    } else if (match("<=")) {
        return Token{TokenType::LEQUAL, "<="};
    } else if (match(">=")) {
        return Token{TokenType::GEQUAL, ">="};
    } else if (match("&&")) {
        return Token{TokenType::AND, "&&"};
    } else if (match("||")) {
        return Token{TokenType::OR, "||"};
    } else if (match("^^")) {
        return Token{TokenType::XOR, "^^"};
    }

    // LEN operator
    if (input[pos] == '|') {
        pos++; // Skip '|'
        size_t start = pos;
        while (pos < input.length() && input[pos] != '|') {
            pos++;
        }
        if (pos >= input.length()) {
            throw std::runtime_error("Unterminated LEN operator");
        }
        std::string value = input.substr(start, pos - start);
        pos++; // Skip closing '|'
        return Token{TokenType::LEN, value};
    }

    // Single-character tokens
    char c = input[pos];
    if (c == '+') {
        pos++;
        return Token{TokenType::PLUS, "+"};
    } else if (c == '-') {
        pos++;
        return Token{TokenType::MINUS, "-"};
    } else if (c == '*') {
        pos++;
        return Token{TokenType::STAR, "*"};
    } else if (c == '/') {
        pos++;
        return Token{TokenType::SLASH, "/"};
    } else if (c == '%') {
        pos++;
        return Token{TokenType::MOD, "%"};
    } else if (c == '=') {
        pos++;
        return Token{TokenType::EQUAL, "="};
    } else if (c == '<') {
        pos++;
        return Token{TokenType::LESS, "<"};
    } else if (c == '>') {
        pos++;
        return Token{TokenType::GREATER, ">"};
    } else if (c == '!') {
        pos++;
        return Token{TokenType::NOT, "!"};
    } else if (c == '(') {
        pos++;
        return Token{TokenType::LPAREN, "("};
    } else if (c == ')') {
        pos++;
        return Token{TokenType::RPAREN, ")"};
    }

    // String literals
    if (c == '"') {
        pos++; // Skip opening '"'
        std::string value;
        while (pos < input.length() && input[pos] != '"') {
            if (input[pos] == '\\' && pos + 1 < input.length()) {
                pos++; // Skip '\'
                value += input[pos];
                pos++;
            } else {
                value += input[pos];
                pos++;
            }
        }
        if (pos >= input.length() || input[pos] != '"') {
            throw std::runtime_error("Unterminated string literal");
        }
        pos++; // Skip closing '"'
        return Token{TokenType::STRING, value};
    }

    // Numbers
    if (std::isdigit(c)) {
        size_t start = pos;
        while (pos < input.length() && std::isdigit(input[pos])) {
            pos++;
        }
        std::string value = input.substr(start, pos - start);
        return Token{TokenType::NUMBER, value};
    }

    // Identifiers and SQL keywords
    if (std::isalpha(c) || c == '_') {
        size_t start = pos;
        while (pos < input.length() && (std::isalnum(input[pos]) || input[pos] == '_')) {
            pos++;
        }
        std::string value = input.substr(start, pos - start);
        TokenType type = identifyKeyword(value);
        return Token{type, value};
    }

    // Unknown token
    throw std::runtime_error("Unknown token at position " + std::to_string(pos));
}

void Tokenizer::skipWhitespace() {
    while (pos < input.length() && std::isspace(input[pos])) {
        pos++;
    }
}

bool Tokenizer::match(const std::string& s) {
    if (input.compare(pos, s.length(), s) == 0) {
        pos += s.length();
        return true;
    }
    return false;
}

TokenType Tokenizer::identifyKeyword(const std::string& value) {
    if (value == "SELECT") return TokenType::SQL_SELECT;
    if (value == "FROM") return TokenType::SQL_FROM;
    if (value == "WHERE") return TokenType::SQL_WHERE;
    if (value == "INSERT") return TokenType::SQL_INSERT;
    if (value == "TO") return TokenType::SQL_TO;
    if (value == "DELETE") return TokenType::SQL_DELETE;
    if (value == "CREATE") return TokenType::SQL_CREATE;
    if (value == "JOIN") return TokenType::SQL_JOIN;
    if (value == "ON") return TokenType::SQL_ON;
    if (value == "UPDATE") return TokenType::SQL_UPDATE;
    if (value == "SET") return TokenType::SQL_SET;
    return TokenType::IDENTIFIER;
}
