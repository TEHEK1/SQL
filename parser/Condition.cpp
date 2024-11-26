#include "Condition.hpp"

std::shared_ptr<Table> Condition::getTableConditionLinear(const std::shared_ptr<Table> & table) const {
    auto tableMeta = table->getTableMeta();
    auto result = std::make_shared<Table>(tableMeta);
    for( auto row : table->getRows()) {
        if(getObjectOperator(row, tableMeta)->getValue<bool>()) {
            table->insertRow(row);
        }
    }
    return result;
}
