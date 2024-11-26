#include "Parser.hpp"

#include <iostream>
#include <ostream>

#include "Table.hpp"
#include "Tokenizer.h"
#include "SeList.hpp"
#include "OperatorIdentifier.hpp"
#include "RelationTable.hpp"
#include "MathParser.h"
#include "RelationJoin.hpp"
#include "InsertToOperatorList.hpp"
#include "InsertToUpdateList.hpp"
#include "InsertTo.hpp"

#include "Attributes.hpp"

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
    std::vector<std::shared_ptr<JoinEqual>> jeList = {};
    while(true) {
        std::shared_ptr<JoinEqual> join_equal = parse_join_equal();
        jeList.push_back(join_equal);
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
    return std::make_shared<SFW>(select_list, relation, where);
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

struct NamedRow {
    std::string name, value;
};
struct UnnamedRow {
    std::string value;
};

static std::shared_ptr<OperatorObject> operatorObjectByToken(const Token &token) {
    if (token.type == TokenType::TRUE) {
        return std::make_shared<OperatorObject>(std::make_shared<Object>(ObjectTypes::BOOL, true));
    }
    if (token.type == TokenType::FALSE) {
        return std::make_shared<OperatorObject>(std::make_shared<Object>(ObjectTypes::BOOL, false));
    }
    if (token.type == TokenType::NUMBER) {
        int value = std::stoi(token.value);
        return std::make_shared<OperatorObject>(std::make_shared<Object>(ObjectTypes::INT32, value));
    }
    if (token.type == TokenType::STRING) {
        return std::make_shared<OperatorObject>(std::make_shared<Object>(ObjectTypes::STRING, token.value));
    }
    throw std::runtime_error("Unexpected token in insert statement. Got " + token.value);
}


std::shared_ptr<InsertTo> Parser::parse_insert_to() {
    Token cur_token = tokenizer.next();
    if(cur_token.type != TokenType::IDENTIFIER) {
        throw std::runtime_error("Expected identifier in TO clause. Expected IDENTIFIER, got " + cur_token.value);
    }

    Token next_token = tokenizer.next();
    UpdateList update_list;
    TableFactory::InsertOperatorList operatorList;
    if(next_token.type == TokenType::EQUAL) {

        next_token = tokenizer.next();
        update_list.emplace_back(cur_token.value, operatorObjectByToken(next_token));

        while (tokenizer.preload_next().type == TokenType::COMMA) {
            tokenizer.next();
            Token name = tokenizer.next();
            if(name.type != TokenType::IDENTIFIER) {
                throw std::runtime_error("Expected identifier while parsing ROW statement in insert. Got " + name.value);
            }
            Token equals = tokenizer.next();
            if(equals.type != TokenType::EQUAL) {
                throw std::runtime_error("Expected = while parsing ROW statement in insert. Got " + equals.value);
            }
            Token value = tokenizer.next();
            if(value.type != TokenType::STRING && value.type != TokenType::NUMBER && value.type != TokenType::TRUE && value.type != TokenType::FALSE) {
                throw std::runtime_error("Expected value while parsing ROW statement in insert. Got " + value.value);
            }
            update_list.emplace_back(name.value, operatorObjectByToken(value));
        }
    }
    if(next_token.type == TokenType::COMMA) {

        long long column_num = 0;
        while(true) {
            next_token = tokenizer.next();
            if(next_token.type == TokenType::COMMA) {
                ++column_num;
                continue;
            }
            operatorList[column_num] = operatorObjectByToken(next_token);
            next_token = tokenizer.next();
            if(next_token.type != TokenType::COMMA) {
                break;
            }
            column_num++;
        }
    }
    next_token = tokenizer.next();
    if(next_token.type != TokenType::SQL_TO) {
        throw std::runtime_error("Expected TO in INSERT statement. Expected TO, got " + next_token.value);
    }
    next_token = tokenizer.next();
    std::shared_ptr<Relation> relation = parse_relation();
    if(!update_list.empty()) {
        return std::dynamic_pointer_cast<InsertTo>(std::make_shared<InsertToUpdateList>(update_list, relation));
    }
    return std::dynamic_pointer_cast<InsertTo>(std::make_shared<InsertToOperatorList>(operatorList, relation));
}

std::shared_ptr<DeleteFrom> Parser::parse_delete() {
    std::shared_ptr<Relation> relation = parse_relation();
    Token next_token = tokenizer.next();
    if(next_token.type != TokenType::SQL_WHERE) {
        throw std::runtime_error("Expected WHERE in DELETE statement. Expected WHERE, got " + next_token.value);
    }
    std::shared_ptr<Condition> where = parse_condition();
    return std::make_shared<DeleteFrom>(relation, where);
}

static Attributes matchTokenToAttribute(const Token& token) {
    if(token.type == TokenType::SQL_KEY) {
        return Attributes::KEY;
    }
    if(token.type == TokenType::SQL_UNIQUE) {
        return Attributes::UNIQUE;
    }
    if(token.type == TokenType::SQL_AUTOINCREMENT) {
        return Attributes::AUTOINCREMENT;
    }
    throw std::runtime_error("Unexpected token in attributes list. Got " + token.value);
}

std::shared_ptr<AttributesSet> Parser::parse_attributes() {
    Token next_token = tokenizer.preload_next();
    if(next_token.type != TokenType::LFIGURE) {
        return {};
    }
    tokenizer.next();
    AttributesSet attributes;
    while(true) {
        next_token = tokenizer.next();
        if(next_token.type != TokenType::IDENTIFIER) {
            throw std::runtime_error("Expected identifier in attributes list. Expected IDENTIFIER, got " + next_token.value);
        }
        attributes.insert(matchTokenToAttribute(next_token));
        next_token = tokenizer.next();
        if(next_token.type == TokenType::RFIGURE) {
            break;
        }
        if(next_token.type != TokenType::COMMA) {
            throw std::runtime_error("Expected comma or RFIGURE in attributes list. Expected COMMA or RFIGURE, got " + next_token.value);
        }
    }
    return std::make_shared<AttributesSet>(attributes);
}

std::shared_ptr<Query> Parser::parse_query(const std::string& s) {
    Token next_token = tokenizer.next();
    while (next_token.type != TokenType::END) {
        if(next_token.type == TokenType::SQL_SELECT) {
            return std::dynamic_pointer_cast<Query>(parse_sfw());
        }
        if(next_token.type == TokenType::SQL_DELETE) {
            return std::dynamic_pointer_cast<Query>(parse_delete());
        }
        if(next_token.type == TokenType::SQL_CREATE) {
            return std::dynamic_pointer_cast<Query>(parse_create_table());
        }
        if(next_token.type == TokenType::SQL_INSERT) {
            return std::dynamic_pointer_cast<Query>(parse_insert_to());
        }
        next_token = tokenizer.next();
    }
}

static ObjectTypes matchTokenToType(const Token& token) {
    if(token.type == TokenType::STRING_TYPE) {
        return ObjectTypes::STRING;
    }
    if(token.type == TokenType::INT32_TYPE) {
        return ObjectTypes::INT32;
    }
    if(token.type == TokenType::BOOL_TYPE) {
        return ObjectTypes::BOOL;
    }
    if(token.type == TokenType::BYTES_TYPE) {
        return ObjectTypes::BYTES;
    }
    throw std::runtime_error("Unexpected token in attributes list. Got " + token.value);
}

std::shared_ptr<Query> Parser::parse_create_table() {
    Token next_token = tokenizer.next();
    if(next_token.type != TokenType::SQL_TABLE) {
        throw std::runtime_error("Expected TABLE in CREATE statement. Expected TABLE, got " + next_token.value);
    }
    next_token = tokenizer.next();
    if(next_token.type != TokenType::IDENTIFIER) {
        throw std::runtime_error("Expected identifier in CREATE statement. Expected IDENTIFIER, got " + next_token.value);
    }
    std::string table_name = next_token.value;
    next_token = tokenizer.next();
    if(next_token.type != TokenType::LPAREN) {
        throw std::runtime_error("Expected ( in CREATE statement. Expected (, got " + next_token.value);
    }
    TableMeta table_meta;
    long long column_num = 0;
    while(true) {
        next_token = tokenizer.next();
        std::shared_ptr<AttributesSet> attributes = parse_attributes();
        next_token = tokenizer.next();
        if(next_token.type != TokenType::IDENTIFIER) {
            throw std::runtime_error("Expected identifier in CREATE statement. Expected IDENTIFIER, got " + next_token.value);
        }
        std::string column_name = next_token.value;
        next_token = tokenizer.next();
        if(next_token.type != TokenType::COLON) {
            throw std::runtime_error("Expected : in CREATE statement. Expected :, got " + next_token.value);
        }
        next_token = tokenizer.next();
        ObjectTypes type = matchTokenToType(next_token);
        next_token = tokenizer.next();
        int size = 0;
        if(type == ObjectTypes::STRING || type == ObjectTypes::BYTES) {
            if(next_token.type != TokenType::LBRACKET) {
                throw std::runtime_error("Expected [ in CREATE statement. Expected [, got " + next_token.value);
            }
            next_token = tokenizer.next();
            if(next_token.type != TokenType::NUMBER) {
                throw std::runtime_error("Expected number in CREATE statement. Expected NUMBER, got " + next_token.value);
            }
            size = std::stoi(next_token.value);
            next_token = tokenizer.next();
            if(next_token.type != TokenType::RBRACKET) {
                throw std::runtime_error("Expected ] in CREATE statement. Expected ], got " + next_token.value);
            }
        }
        next_token = tokenizer.preload_next();
        std::shared_ptr<Object> defaultValue = nullptr;
        if(next_token.type == TokenType::EQUAL) {
            tokenizer.next();
            next_token = tokenizer.next();
            if(next_token.type == TokenType::TRUE) {
                defaultValue = std::make_shared<Object>(ObjectTypes::BOOL, true);
            }
            if(next_token.type == TokenType::FALSE) {
                defaultValue = std::make_shared<Object>(ObjectTypes::BOOL, false);
            }
            if(next_token.type == TokenType::NUMBER) {
                int value = std::stoi(next_token.value);
                defaultValue = std::make_shared<Object>(ObjectTypes::INT32, value);
            }
            if(next_token.type == TokenType::STRING) {
                defaultValue = std::make_shared<Object>(ObjectTypes::STRING, next_token.value);
            }
            if (defaultValue == nullptr) {
                throw std::runtime_error("Unexpected token in CREATE statement. Got " + next_token.value);
            }
            if (defaultValue -> getType() != type) {
                throw std::runtime_error("Type mismatch in CREATE statement. Default value type does not match column type");
            }
        }
        std::shared_ptr<ColumnMeta> column_meta = std::make_shared<ColumnMeta>(column_num, type, *attributes, 0, size, defaultValue);
        table_meta.setByName(column_name, column_meta);
        next_token = tokenizer.next();
        if(next_token.type != TokenType::COMMA) {
            break;
        }
    }
    if(next_token.type != TokenType::RPAREN) {
        throw std::runtime_error("Expected ) in CREATE statement. Expected ), got " + next_token.value);
    }

}

