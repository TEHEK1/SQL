#include "ConditionAnd.hpp"
ConditionAnd::ConditionAnd(const std::shared_ptr<Condition>& leftCondition,
                           const std::shared_ptr<Condition>& rightCondition) :
                           m_leftCondition(leftCondition), m_rightCondition(rightCondition){}

std::shared_ptr<Table> ConditionAnd::execute(const std::shared_ptr<Table> & table) {
    auto table1 = m_leftCondition->execute(table);
    return m_rightCondition->execute(table1);
}