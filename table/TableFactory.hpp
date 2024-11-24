#pragma once
#include "Table.hpp"

class TableFactory {
public:
    Table TableAndTable(const Table& table1, const Table& table2); // returns && result O(n + m)
    Table TableOrTable(const Table& table1, const Table& table2); // returns || result O(n + m)
    Table TableJoinTable(const Table& table)
};
