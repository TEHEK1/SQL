#include "UpdateEqual.hpp"

UpdateEqual::UpdateEqual(const std::string & columnName, const std::shared_ptr<Operator> & resultOperator) :
                            m_columnName(columnName), m_resultOperator(resultOperator) {}

bool UpdateEqual::execute(std::shared_ptr<Row> & row, const std::shared_ptr<TableMeta>& tableMeta) const {

}
