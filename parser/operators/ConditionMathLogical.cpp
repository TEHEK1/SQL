#include "ConditionMathLogical.hpp"

std::shared_ptr<Table> ConditionMathLogical::getTableCondition(const std::shared_ptr<Table> & table) const {
    return getTableConditionLinear(table);
}

std::shared_ptr<Object> ConditionMathLogical::getObjectOperator(const std::shared_ptr<Row> & row, const TableMeta & tableMeta) const {
    const auto object1 = m_condition1->getObjectOperator(row, tableMeta);
    const auto object2 = m_condition2->getObjectOperator(row, tableMeta);
    switch (m_tokenType) {
        case TokenType::AND:
            if(object1->getType() == ObjectTypes::INT32 && object2->getType() == ObjectTypes::INT32) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<int32_t>() < object2->getValue<int32_t>());
            }
            else if(object1->getType() == ObjectTypes::STRING && object2->getType() == ObjectTypes::STRING) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<std::string>() < object2->getValue<std::string>());
            }
            else {
                throw std::runtime_error("&& accepts only bool");
            }
            break;
        case TokenType::OR:
            if(object1->getType() == ObjectTypes::BOOL && object2->getType() == ObjectTypes::BOOL) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<bool>() || object2->getValue<bool>());
            }
            else {
                throw std::runtime_error("|| accepts only bool");
            }
            break;
        case TokenType::XOR:
            if(object1->getType() == ObjectTypes::BOOL && object2->getType() == ObjectTypes::BOOL) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<bool>() ^ object2->getValue<bool>());
            }
            else {
                throw std::runtime_error("^^ accepts only bool");
            }
            break;
        default:
            throw std::runtime_error("Math operator got not math token");
    }
}
