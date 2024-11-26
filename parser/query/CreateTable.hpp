#pragma once
#include "Query.hpp"
#include "TableMeta.hpp"

class CreateTable : public Query {
public:
    CreateTable(const std::string&, const TableMeta& );
    bool executeQuery(const std::shared_ptr<DataBase> &) const override;
    ~CreateTable() override =default;
private:
    std::string m_tableName;
    TableMeta m_tableMeta;
};
