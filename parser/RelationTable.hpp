#pragma once
#include <string>
#include "Relation.hpp"
class RelationTable : public Relation {
public:
    explicit RelationTable(const std::string &);
    std::shared_ptr<Table> getTableRelation(const std::shared_ptr<DataBase> &) const override;
    std::string getName() const override;
    ~RelationTable() override = default;
private:
    std::string m_tableName;
};
