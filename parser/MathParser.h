#pragma once
#include <map>
#include <memory>
#include <vector>

enum class TokenType;
class ASTNode;
struct Token;

class MathParser {
public:
    MathParser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

    std::unique_ptr<ASTNode> parse_expression(int min_precedence = 0);

private:
    const std::vector<Token>& tokens;
    size_t pos;

    const Token& current_token();
    void advance();
    bool match(TokenType type);

    std::unique_ptr<ASTNode> parse_primary_expression();

    // Precedence and associativity
    static std::map<TokenType, int> precedence_map;
    static int get_precedence(TokenType type);
};
