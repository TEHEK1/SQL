#include "DataBase.hpp"

std::shared_ptr<Table> DataBase::getTable(const std::string& tableName) const {
   if(tables.find(tableName) == tables.end()) {
      throw std::runtime_error("no such database");
   }
   return tables.find(tableName) -> second;
}

bool DataBase::insertTable(const std::string& tableName, const std::shared_ptr<Table>& Information) {
   if(tables.find(tableName) != tables.end()) {
      throw std::runtime_error("there is already such a table");
   }
   tables[tableName] = Information;
   return true;
}