#include "SeList.hpp"
#include "ObjectFactory.hpp"

SeList::SeList(const std::vector<std::shared_ptr<Operator>>& columns) : m_columns(columns) {}

std::shared_ptr<Table> SeList::execute(const std::shared_ptr<Table> & table) {

    TableMeta resultTableMeta;
    {
        long long current_column_num = 0;
        for (const auto& column: m_columns) {
            resultTableMeta.setByName("", std::make_shared<ColumnMeta>(current_column_num, column->execute(std::shared_ptr<Row>(), table->getTableMeta())->getType()));
            current_column_num++;
        }
    }
    auto result = std::make_shared<Table>(resultTableMeta);
    for(const auto& row : table->getRows())
    {
        std::vector<std::shared_ptr<Object>> newRow{};
        newRow.reserve(m_columns.size());
        for (const auto& column: m_columns) {
            newRow.push_back(column->execute(row, table->getTableMeta()));
        }
        table->insertRow(std::make_shared<Row>(newRow));
    }

    return result;
}
