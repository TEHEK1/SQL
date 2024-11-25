#pragma once
#include <string>
#include "Relation.hpp"
class RelationTable : public Relation {
public:
    explicit RelationTable(const std::string &);
    [[nodiscard]] std::shared_ptr<Table> execute(const std::shared_ptr<DataBase> &) const override;
private:
    std::string m_tableName;
};
