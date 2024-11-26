#include "JoinEqualList.hpp"
#include "RowFactory.hpp"
#include "TableFactory.hpp"
JoinEqualList::JoinEqualList(const std::vector<std::shared_ptr<JoinEqual>> &joinEquals) : m_joinEquals(joinEquals) {}

std::shared_ptr<Table> JoinEqualList::execute(const std::string &tableName1, const std::shared_ptr<Table> &table1, const std::string &tableName2,
                             const std::shared_ptr<Table> &table2) {
    return TableFactory::joinTables(table1, tableName1, table2, tableName2, m_joinEquals);
}