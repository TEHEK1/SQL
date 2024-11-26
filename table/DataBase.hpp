#pragma once
#include <memory>
#include <unordered_map>
#include "Table.hpp"

class DataBase {
    public:
        bool insertTable(const std::string& tableName, const std::shared_ptr<Table>&);
        std::shared_ptr<Table> getTable(const std::string& tableName) const;
    private:
        std::unordered_map<std::string, std::shared_ptr<Table> > tables;
};
