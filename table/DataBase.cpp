#include "DataBase.hpp"

std::shared_ptr<Table> DataBase::getTable(const std::string& tableName) const {
   if(tables.find(tableName) != tables.end()) {
      throw std::runtime_error("no such database");
   }
   return tables.find(tableName) -> second;
}