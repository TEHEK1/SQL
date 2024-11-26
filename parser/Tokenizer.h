#pragma once
#include <string>
#include <stdexcept>
#include <cctype>

enum class TokenType {
    IDENTIFIER, // [a-zA-Z_][a-zA-Z0-9_]*
    COMMA,      // ,
    STRING,     // ".*"
    BYTES,      // 0x.*
    NUMBER,     // [0-9]+
    PLUS,       // +
    MINUS,      // -
    STAR,       // *
    SLASH,      // /
    MOD,        // %
    LEN,        // |string| will be represented as LEN string
    EQUAL,      // =
    NEQUAL,     // !=
    LESS,       // <
    GREATER,    // >
    LEQUAL,     // <=
    GEQUAL,     // >=
    AND,        // &&
    OR,         // ||
    NOT,        // !
    LPAREN,     // (
    RPAREN,     // )
    XOR,        // ^^
    TRUE,       // true
    FALSE,      // false
    SQL_SELECT, // SELECT
    SQL_FROM,   // FROM
    SQL_WHERE,  // WHERE
    SQL_INSERT, // INSERT
    SQL_TO,     // TO
    SQL_DELETE, // DELETE
    SQL_CREATE, // CREATE
    SQL_JOIN,   // JOIN
    SQL_ON,     // ON
    SQL_UPDATE, // UPDATE
    SQL_TABLE,  // TABLE
    SQL_SET,    // SET
    END         // end of input
};

struct Token {
    TokenType type;
    std::string value;
};

class Tokenizer {
public:
    explicit Tokenizer(const std::string& str);
    Token preload_next();
    Token next();

private:
    void skipWhitespace();
    bool match(const std::string& s);
    TokenType identifyKeyword(const std::string& value);

    std::string input;
    size_t pos;
};
