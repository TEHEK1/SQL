#include "CreateTable.hpp"

CreateTable::CreateTable(const std::string & tableName, const TableMeta & tableMeta) : m_tableName(tableName), m_tableMeta(tableMeta) {}

bool CreateTable::executeQuery(const std::shared_ptr<DataBase> & dataBase) const {
    dataBase->insertTable(m_tableName, std::make_shared<Table>(m_tableMeta));
    return true;
}
