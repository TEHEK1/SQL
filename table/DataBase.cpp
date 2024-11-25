#include "DataBase.hpp"

std::shared_ptr<Table> DataBase::getTable(const std::string& tableName) {
   return tables[tableName];
}