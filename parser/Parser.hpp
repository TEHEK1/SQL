#pragma once
#include <string>
#include "DataBase.hpp"
#include "Tokenizer.h"
#include "Condition.hpp"


class Parser {
    Tokenizer tokenizer;
    std::shared_ptr<JoinEqual> parse_join_equal();
    std::shared_ptr<JoinEqualList> parse_join_equal_list();
    std::shared_ptr<Condition> parse_condition() const;
    std::shared_ptr<SeList> parse_selist();
    std::shared_ptr<Relation> parse_relation();

    std::shared_ptr<SFW> parse_sfw();
    std::shared_ptr<>
public:
    Parser(Tokenizer &tokenizer);
    std::shared_ptr<Query> parse_query(const std::string &s);
};
