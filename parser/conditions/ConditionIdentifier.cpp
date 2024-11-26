#include "ConditionIdentifier.hpp"
#include "ObjectFactory.hpp"
ConditionIdentifier::ConditionIdentifier(const std::string & columnName) : m_columnName(columnName) {

}

std::shared_ptr<Table> ConditionIdentifier::getTableCondition(const std::shared_ptr<Table> & table) const {
    return getTableConditionLinear(table);
}

std::shared_ptr<Object> ConditionIdentifier::getObjectOperator(const std::shared_ptr<Row> & row, const TableMeta & tableMeta) const {
    return ObjectFactory::getObjectByColumnName(m_columnName, row, tableMeta);
}
