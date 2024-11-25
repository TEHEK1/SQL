#include "JoinEqualList.hpp"
#include "RowFactory.hpp"
JoinEqualList::JoinEqualList(const std::vector<std::shared_ptr<JoinEqual>> &joinEquals) : m_joinEquals(joinEquals) {}

std::shared_ptr<Table> JoinEqualList::execute(const std::string &tableName1, const std::shared_ptr<Table> &table1, const std::string &tableName2,
                             const std::shared_ptr<Table> &table2) {
    TableMeta resultTableMeta;
    {
        size_t offset = 0;
        for(const auto& [tableMeta, tableName]:{std::pair{table1->getTableMeta(), tableName1}, std::pair{table2->getTableMeta(), tableName2}}){
            for(const auto& [name, columnMeta] : tableMeta.getNameColumnMetas()) {
                resultTableMeta.setByName(tableName + "." + name, std::make_shared<ColumnMeta>(*columnMeta, columnMeta->getRealColumnNum() + offset));
            }
            offset += tableMeta.size();
        }
    }
    auto result = std::make_shared<Table>(resultTableMeta);
    auto joinEqual = m_joinEquals[0];
    for(const auto& row1:table1->getRows()) {
        auto filtered = joinEqual->execute(row1, table1->getTableMeta(), table2);
        for(const auto& row2:filtered->getRows()) {
            auto current_row = RowFactory::concatenateRow(row1, row2);
            result->insertRow(current_row);
        }
    }
}