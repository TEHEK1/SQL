#pragma once
#include <string>
#include "Relation.hpp"
class RelationTable : Relation {
    RelationTable(const std::string &);
    std::shared_ptr<Table> execute(const std::shared_ptr<DataBase> &) override;
};
