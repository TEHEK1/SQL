#include "RelationTable.hpp"

std::shared_ptr<Table> RelationTable::execute(const std::shared_ptr<DataBase> & dataBase) const {
    return dataBase->getTable(m_tableName);
}
