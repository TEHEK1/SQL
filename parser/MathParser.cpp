#include "MathParser.h"

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <memory>
#include <map>

enum class TokenType {
    // Single-character tokens
    PLUS,           // '+'
    MINUS,          // '-'
    STAR,           // '*'
    SLASH,          // '/'
    PERCENT,        // '%'
    CARET,          // '^' (exponentiation)
    LPAREN,         // '('
    RPAREN,         // ')'
    NOT,            // '!'
    LESS,           // '<'
    GREATER,        // '>'

    // One or two character tokens
    EQUAL_EQUAL,    // '=' (equality test)
    BANG_EQUAL,     // '!='
    LESS_EQUAL,     // '<='
    GREATER_EQUAL,  // '>='
    AND_AND,        // '&&'
    OR_OR,          // '||'
    BITXOR,         // '^^' (bitwise XOR)

    // Literals
    IDENTIFIER,
    NUMBER,

    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string text;

    Token(TokenType type, const std::string& text) : type(type), text(text) {}
};

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    size_t i = 0;
    size_t length = input.length();

    while (i < length) {
        char c = input[i];

        // Skip whitespace
        if (isspace(c)) {
            ++i;
            continue;
        }

        // Handle numbers (integer and floating point)
        if (isdigit(c) || c == '.') {
            size_t start = i;
            bool has_dot = (c == '.');
            ++i;
            while (i < length && (isdigit(input[i]) || (!has_dot && input[i] == '.'))) {
                if (input[i] == '.') has_dot = true;
                ++i;
            }
            tokens.emplace_back(TokenType::NUMBER, input.substr(start, i - start));
            continue;
        }

        // Handle identifiers
        if (isalpha(c) || c == '_') {
            size_t start = i;
            ++i;
            while (i < length && (isalnum(input[i]) || input[i] == '_')) {
                ++i;
            }
            tokens.emplace_back(TokenType::IDENTIFIER, input.substr(start, i - start));
            continue;
        }

        // Handle operators and punctuators
        switch (c) {
            case '+':
                tokens.emplace_back(TokenType::PLUS, "+");
                ++i;
                break;
            case '-':
                tokens.emplace_back(TokenType::MINUS, "-");
                ++i;
                break;
            case '*':
                tokens.emplace_back(TokenType::STAR, "*");
                ++i;
                break;
            case '/':
                tokens.emplace_back(TokenType::SLASH, "/");
                ++i;
                break;
            case '%':
                tokens.emplace_back(TokenType::PERCENT, "%");
                ++i;
                break;
            case '^':
                // Need to check if it's '^^' or '^'
                if (i + 1 < length && input[i + 1] == '^') {
                    tokens.emplace_back(TokenType::BITXOR, "^^");
                    i += 2;
                } else {
                    tokens.emplace_back(TokenType::CARET, "^");
                    ++i;
                }
                break;
            case '!':
                if (i + 1 < length && input[i + 1] == '=') {
                    tokens.emplace_back(TokenType::BANG_EQUAL, "!=");
                    i += 2;
                } else {
                    tokens.emplace_back(TokenType::NOT, "!");
                    ++i;
                }
                break;
            case '=':
                tokens.emplace_back(TokenType::EQUAL_EQUAL, "=");
                ++i;
                break;
            case '<':
                if (i + 1 < length && input[i + 1] == '=') {
                    tokens.emplace_back(TokenType::LESS_EQUAL, "<=");
                    i += 2;
                } else {
                    tokens.emplace_back(TokenType::LESS, "<");
                    ++i;
                }
                break;
            case '>':
                if (i + 1 < length && input[i + 1] == '=') {
                    tokens.emplace_back(TokenType::GREATER_EQUAL, ">=");
                    i += 2;
                } else {
                    tokens.emplace_back(TokenType::GREATER, ">");
                    ++i;
                }
                break;
            case '&':
                if (i + 1 < length && input[i + 1] == '&') {
                    tokens.emplace_back(TokenType::AND_AND, "&&");
                    i += 2;
                } else {
                    tokens.emplace_back(TokenType::UNKNOWN, "&");
                    ++i;
                }
                break;
            case '|':
                if (i + 1 < length && input[i + 1] == '|') {
                    tokens.emplace_back(TokenType::OR_OR, "||");
                    i += 2;
                } else {
                    tokens.emplace_back(TokenType::UNKNOWN, "|");
                    ++i;
                }
                break;
            case '(':
                tokens.emplace_back(TokenType::LPAREN, "(");
                ++i;
                break;
            case ')':
                tokens.emplace_back(TokenType::RPAREN, ")");
                ++i;
                break;
            default:
                tokens.emplace_back(TokenType::UNKNOWN, std::string(1, c));
                ++i;
                break;
        }
    }
    tokens.emplace_back(TokenType::END_OF_FILE, "");
    return tokens;
}

class ASTNode {
public:
    virtual ~ASTNode() {}
    virtual void print(int indent = 0) const = 0;
};

class NumberNode : public ASTNode {
public:
    std::string value;

    NumberNode(const std::string& value) : value(value) {}

    void print(int indent = 0) const override {
        for(int i = 0; i < indent; ++i) std::cout << "  ";
        std::cout << "Number(" << value << ")\n";
    }
};

class IdentifierNode : public ASTNode {
public:
    std::string name;

    IdentifierNode(const std::string& name) : name(name) {}

    void print(int indent = 0) const override {
        for(int i = 0; i < indent; ++i) std::cout << "  ";
        std::cout << "Identifier(" << name << ")\n";
    }
};

class BinaryOpNode : public ASTNode {
public:
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    BinaryOpNode(const std::string& op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
        : op(op), left(std::move(left)), right(std::move(right)) {}

    void print(int indent = 0) const override {
        for(int i = 0; i < indent; ++i) std::cout << "  ";
        std::cout << "BinaryOp(" << op << ")\n";
        if (left) left->print(indent + 1);
        if (right) right->print(indent + 1);
    }
};

class UnaryOpNode : public ASTNode {
public:
    std::string op;
    std::unique_ptr<ASTNode> operand;

    UnaryOpNode(const std::string& op, std::unique_ptr<ASTNode> operand)
        : op(op), operand(std::move(operand)) {}

    void print(int indent = 0) const override {
        for(int i = 0; i < indent; ++i) std::cout << "  ";
        std::cout << "UnaryOp(" << op << ")\n";
        if (operand) operand->print(indent + 1);
    }
};



// Define operator precedence
std::map<TokenType, int> MathParser::precedence_map = {
    {TokenType::OR_OR,          1},
    {TokenType::AND_AND,        2},
    {TokenType::BITXOR,         3},
    {TokenType::EQUAL_EQUAL,    4},
    {TokenType::BANG_EQUAL,     4},
    {TokenType::LESS,           5},
    {TokenType::LESS_EQUAL,     5},
    {TokenType::GREATER,        5},
    {TokenType::GREATER_EQUAL,  5},
    {TokenType::PLUS,           6},
    {TokenType::MINUS,          6},
    {TokenType::STAR,           7},
    {TokenType::SLASH,          7},
    {TokenType::PERCENT,        7},
    {TokenType::CARET,          8}, // Exponentiation
    {TokenType::EQUAL_EQUAL,    9}, // Assignment (note that '=' is used for '==')
};

int MathParser::get_precedence(TokenType type) {
    auto it = precedence_map.find(type);
    if (it != precedence_map.end()) {
        return it->second;
    }
    return -1;
}

const Token& MathParser::current_token() {
    if (pos < tokens.size()) {
        return tokens[pos];
    } else {
        static Token eof_token(TokenType::END_OF_FILE, "");
        return eof_token;
    }
}

void MathParser::advance() {
    if (pos < tokens.size()) {
        ++pos;
    }
}

bool MathParser::match(TokenType type) {
    if (current_token().type == type) {
        advance();
        return true;
    }
    return false;
}

std::unique_ptr<ASTNode> MathParser::parse_expression(int min_precedence) {
    std::unique_ptr<ASTNode> left;

    // Parse unary operators
    if (current_token().type == TokenType::PLUS ||
        current_token().type == TokenType::MINUS ||
        current_token().type == TokenType::NOT) {
        std::string op = current_token().text;
        advance();
        std::unique_ptr<ASTNode> operand = parse_expression(9); // High precedence for unary operators
        left = std::make_unique<UnaryOpNode>(op, std::move(operand));
    } else {
        left = parse_primary_expression();
    }

    while (true) {
        TokenType op_type = current_token().type;
        int precedence = get_precedence(op_type);

        if (precedence < min_precedence) {
            break;
        }

        std::string op = current_token().text;
        advance();

        // For left-associative operators, the next min_precedence is precedence + 1
        int next_min_precedence = precedence + 1;

        std::unique_ptr<ASTNode> right = parse_expression(next_min_precedence);

        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<ASTNode> MathParser::parse_primary_expression() {
    if (match(TokenType::NUMBER)) {
        std::string value = tokens[pos - 1].text;
        return std::make_unique<NumberNode>(value);
    } else if (match(TokenType::IDENTIFIER)) {
        std::string name = tokens[pos - 1].text;
        return std::make_unique<IdentifierNode>(name);
    } else if (match(TokenType::LPAREN)) {
        std::unique_ptr<ASTNode> expr = parse_expression();
        if (!match(TokenType::RPAREN)) {
            std::cerr << "Error: Expected ')' at position " << pos << "\n";
        }
        return expr;
    } else {
        std::cerr << "Error: Unexpected token '" << current_token().text << "' at position " << pos << "\n";
        advance();
        return nullptr;
    }
}