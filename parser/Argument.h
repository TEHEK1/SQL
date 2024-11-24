#pragma once
#include <any>
#include <string>
#include <vector>

class Relation {
    Relation(const std::string &s);
    Relation(Relation &&r) noexcept ;
};

class Query {
public:
    virtual ~Query() = default;

private:
    Query();
    virtual Relation execute() = 0;
};

class Attribute {
    std::string s;
    Attribute(const std::string &s);
};


class SeList {
    SeList(const std::vector<Attribute> &attributes);
};

class Condition {

};

class RelationList {
    RelationList(const std::vector<Relation> &relations);
};

class SFW : Query { //SFW = Select ... from .. where
    SFW(const SeList& se_list, const RelationList& from_list, const Condition& condition):Query() {};
    Relation execute() override;
};

class JoinOn : Query {
    JoinOn(const Relation &r1, const Relation &r2, const Condition &condition):Query() {};
    Relation execute() override;
};

class Literal {
    std::any value;
    Literal(int x);
    Literal(bool x);
    Literal(std::string x);
    Literal(std::vector<std::byte> x);
};

class InsertLine {
    std::vector<std::pair<Attribute, Literal>> values;
    InsertLine(const std::vector<std::pair<Attribute, Literal>> &values);
};

class InsertTO: Query {
    InsertTO(const InsertLine &line, const Relation &relation):Query() {};
    Relation execute() override;
};

class DeleteFrom: Query {
    DeleteFrom(const Relation &relation, const Condition &condition):Query() {};
    Relation execute() override;
};