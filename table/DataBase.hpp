#pragma once
#include <memory>
#include <unordered_map>
#include "Table.hpp"
class DataBase {
public:
    std::shared_ptr<Table> getTable(const std::string& tableName);
private:
    std::unordered_map<std::string, std::shared_ptr<Table> > tables;
};
