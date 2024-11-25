#include "Parser.hpp"

#include <iostream>
#include <ostream>

#include "Tokenizer.h"
#include "SeList.hpp"
#include "OperatorIdentifier.hpp"
#include "RelationTable.hpp"
#include "MathParser.h"


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

std::shared_ptr<JoinEqualList> Parser::parse_join_equal_list() {
    std::vector<JoinEqual> jeList = {};
    while(true) {
        std::shared_ptr<JoinEqual> join_equal = parse_join_equal();
        jeList.push_back(*join_equal);
        Token next_token = tokenizer.preload_next();
        if (next_token.type != TokenType::COMMA) {
            return std::make_shared<JoinEqualList>(jeList);
        }
    }
}

std::shared_ptr<JoinEqual> Parser::parse_join_equal() {
    Token next_token = tokenizer.next();
    if(next_token.type != TokenType::IDENTIFIER) {
        throw std::runtime_error("Expected identifier in equal list of JOIN clause. Expected IDENTIFIER, got " + next_token.value);
    }
    std::string first_part = next_token.value;
    next_token = tokenizer.next();
    if(next_token.type != TokenType::EQUAL) {
        throw std::runtime_error("Expected = in equal list of JOIN clause. Expected =, got " + next_token.value);
    }
    next_token = tokenizer.next();
    if(next_token.type != TokenType::IDENTIFIER) {
        throw std::runtime_error("Expected identifier in equal list of JOIN clause. Expected IDENTIFIER, got " + next_token.value);
    }
    std::string second_part = next_token.value;
    return std::make_shared<JoinEqual>(first_part, second_part);
}



std::shared_ptr<Relation> Parser::parse_relation() {
    Token next_token = tokenizer.next();
    if(next_token.type != TokenType::IDENTIFIER) {
        throw std::runtime_error("Expected identifier in FROM clause. Expected IDENTIFIER, got " + next_token.value);
    }
    std::shared_ptr<Relation> first_part = std::make_shared<RelationTable>(next_token.value);
    if(tokenizer.preload_next().type == TokenType::SQL_JOIN) {
        tokenizer.next();
        std::shared_ptr<Relation> second_part = parse_relation();
        next_token = tokenizer.preload_next();
        if(next_token.type != TokenType::SQL_ON) {
            throw std::runtime_error("Expected ON in JOIN clause. Expected ON, got " + next_token.value);
        }
        tokenizer.next();
        std::shared_ptr<JoinEqualList> join_equal_list = parse_join_equal_list();
        return std::make_shared<RelationJoin>(first_part, second_part, join_equal_list);
    }
    return first_part;
}



std::shared_ptr<SFW> Parser::parse_sfw() {
    std::shared_ptr<SeList> select_list = parse_selist();
    std::shared_ptr<Relation> relation = parse_relation();
    Token next_token = tokenizer.next();
    if(next_token.type != TokenType::SQL_WHERE) {
        throw std::runtime_error("Expected WHERE in SELECT statement. Expected WHERE, got " + next_token.value);
    }
    std::shared_ptr<Condition> where = parse_condition();
    return std::make_shared<SFW>(*select_list, *relation, *where);
}

std::shared_ptr<Condition> Parser::parse_condition() const {
    MathParser mathParser(tokenizer);
    std::shared_ptr<Condition> ret = nullptr;
    try {
        ret = mathParser.parse();
    } catch (const std::runtime_error& e) {
        std::cerr << "Math parsing error: " << e.what() << std::endl;
        throw;
    }
    return ret;
}



std::shared_ptr<Query> Parser::parse_query(const std::string& s) {
    Token next_token = tokenizer.next();
    while (next_token.type != TokenType::END) {
        if(next_token.type == TokenType::SQL_SELECT) {
            return std::dynamic_pointer_cast<Query>(parse_sfw());
        }
        if(next_token.type == TokenType::SQL_CREATE) {
            return std::dynamic_pointer_cast<Query>(parse_create_table());
        }
        next_token = tokenizer.next();
    }
}

