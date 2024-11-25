#pragma once
#include <any>
#include <string>
#include <vector>
#include <SeList.hpp>
#include <Relation.hpp>
#include <RelationJoin.hpp>
#include <Condition.hpp>

class Query {
public:
    virtual ~Query() = default;

protected:
    Query();
    virtual void execute() = 0;
};

class SFW : public Query { //SFW = Select ... from .. where
    SFW(const SeList& se_list, const Relation& from_list, const Condition& condition):Query() {};
    void execute() override;
};

class CreateTable : public Query {
    CreateTable(const Relation &relation):Query() {};
    void execute() override;
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