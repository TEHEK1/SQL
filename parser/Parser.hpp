#pragma once
#include <string>
#include "DataBase.hpp"
#include "Tokenizer.h"

class Parser {
    Tokenizer tokenizer;
    std::shared_ptr<SFW> parse_sfw();
    std::shared_ptr<SeList> parse_selist();
    std::shared_ptr<Relation> parse_relation();
public:
    Parser(Tokenizer &tokenizer);
    std::shared_ptr<Query> parse_query(const std::string &s);
};
