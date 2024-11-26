#include "RelationTable.hpp"

RelationTable::RelationTable(const std::string & tableName) : m_tableName(tableName) {}

std::shared_ptr<Table> RelationTable::getTableRelation(const std::shared_ptr<DataBase> & dataBase) const {
    return dataBase->getTable(m_tableName);
}

std::string RelationTable::getName() const {
    return m_tableName;
}


