#pragma once
#include <string>
#include "Relation.hpp"
#include "JoinEqual.hpp"
#include "JoinEqualList.hpp"
#include "SeList.hpp"
#include "query/SFW.hpp"
#include "query/DeleteFrom.hpp"
#include "DataBase.hpp"
#include "Tokenizer.h"
#include "Condition.hpp"
#include "InsertTo.hpp"


class Parser {
    Tokenizer tokenizer;
    std::shared_ptr<JoinEqual> parse_join_equal();
    std::shared_ptr<JoinEqualList> parse_join_equal_list();
    std::shared_ptr<Condition> parse_condition() const;
    std::shared_ptr<SeList> parse_selist();
    std::shared_ptr<Relation> parse_relation();
    std::shared_ptr<AttributesSet> parse_attributes();

    // Query parsers
    std::shared_ptr<DeleteFrom> parse_delete();
    std::shared_ptr<Query> parse_create_table();
    std::shared_ptr<SFW> parse_sfw();
    std::shared_ptr<InsertTo> parse_insert_to();
public:
    Parser(Tokenizer &tokenizer);
    std::shared_ptr<Query> parse_query(const std::string &s);
};
