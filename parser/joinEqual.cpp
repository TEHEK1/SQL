#include "JoinEqual.hpp"
#include "TableFactory.hpp"
#include "ObjectFactory.hpp"

JoinEqual::JoinEqual(const std::string& columnName1, const std::string& columnName2): m_columnName1(columnName1), m_columnName2(columnName2) {

}

std::shared_ptr<Table> JoinEqual::execute(const std::shared_ptr<Row> &row, const TableMeta &columnMeta, const std::shared_ptr<Table> & table) const{
    return TableFactory::filter_equal(m_columnName2, ObjectFactory::getObjectByColumnName(m_columnName1, row, columnMeta),  table);
}
