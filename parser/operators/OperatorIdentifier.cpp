#include "OperatorIdentifier.hpp"
#include "ObjectFactory.hpp"
OperatorIdentifier::OperatorIdentifier(const std::string & columnName) : m_columnName(columnName) {}

std::shared_ptr<Object> OperatorIdentifier::getObjectOperator(const std::shared_ptr<Row> & row, const TableMeta & tableMeta) const {
    return ObjectFactory::getObjectByColumnName(m_columnName, row, tableMeta);
}

ObjectTypes OperatorIdentifier::getTypeOperator(const TableMeta &tableMeta) const {
    return tableMeta.getByName(m_columnName)->getType();
}


