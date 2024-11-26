#include "ConditionIdentifier.hpp"

ConditionIdentifier::ConditionIdentifier(const std::string & columnName) : m_columnName(columnName) {

}

std::shared_ptr<Table> ConditionIdentifier::getTableCondition(const std::shared_ptr<Table> &) const {

    return std::shared_ptr<Table>();
}
