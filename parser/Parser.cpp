#include "Parser.hpp"

#include "Tokenizer.h"
#include "SeList.hpp"
#include "OperatorIdentifier.hpp"

Parser::Parser(Tokenizer &tokenizer) : tokenizer(tokenizer) {}

std::shared_ptr<SeList> Parser::parse_selist() {
    Token next_token = tokenizer.next();
    std::vector<std::shared_ptr<Operator> > columns;
    while (true) {
        if(next_token.type != TokenType::IDENTIFIER) {
            throw std::runtime_error("Expected identifier in SELECT list. Expected IDENTIFIER, got " + next_token.value);
        }
        columns.emplace_back(std::make_shared<OperatorIdentifier>(next_token.value));
        next_token = tokenizer.next();
        if(next_token.type == TokenType::SQL_FROM) {
            break;
        }
        if(next_token.type != TokenType::COMMA) {
            throw std::runtime_error("Expected comma or FROM in SELECT list. Expected COMMA or FROM, got " + next_token.value);
        }
        next_token = tokenizer.next();
    }
    return std::make_shared<SeList>(columns);
}

std::shared_ptr<Relation> Parser::parse_relation() {
    Token next_token = tokenizer.next();
    if(next_token.type == TokenType::IDENTIFIER) {
        return std::make_shared<Relation>(next_token.value);
    }
}


std::shared_ptr<SFW> Parser::parse_sfw() {
    //Parse SeList
    std::shared_ptr<SeList> select_list = parse_selist();
    std::shared_ptr<Relation> relation = parse_relation();
}

std::shared_ptr<Query> Parser::parse_query(const std::string& s) {
    Token next_token = tokenizer.next();
    while (next_token.type != TokenType::END) {
        if(next_token.type == TokenType::SQL_SELECT) {
            return std::dynamic_pointer_cast<Query>(parse_sfw());
        }
        //TODO more
        next_token = tokenizer.next();
    }
}

