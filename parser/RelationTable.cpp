#include "RelationTable.hpp"

RelationTable::RelationTable(const std::string & tableName) : m_tableName(tableName) {}

std::shared_ptr<Table> RelationTable::execute(const std::shared_ptr<DataBase> & dataBase) const {
    return dataBase->getTable(m_tableName);
}


