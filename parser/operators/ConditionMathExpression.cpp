#include "ConditionMathExpression.hpp"

ConditionMathExpression::ConditionMathExpression(const std::shared_ptr<Operator> & operator1,
        const std::shared_ptr<Operator> & operator2, TokenType tokenType) : m_operator1(operator1), m_operator2(operator2), m_tokenType(tokenType) {}

std::shared_ptr<Table> ConditionMathExpression::getTableCondition(const std::shared_ptr<Table> & table) const {
    return getTableConditionLinear(table);
}
std::shared_ptr<Object> ConditionMathExpression::getObjectOperator(const std::shared_ptr<Row> & row, const TableMeta & tableMeta) const {
    const auto object1 = m_operator1->getObjectOperator(row, tableMeta);
    const auto object2 = m_operator2->getObjectOperator(row, tableMeta);
    switch (m_tokenType) {
        case TokenType::LESS:
            if(object1->getType() == ObjectTypes::INT32 && object2->getType() == ObjectTypes::INT32) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<int32_t>() < object2->getValue<int32_t>());
            }
            else if(object1->getType() == ObjectTypes::STRING && object2->getType() == ObjectTypes::STRING) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<std::string>() < object2->getValue<std::string>());
            }
            else {
                throw std::runtime_error("< accepts only string and int32");
            }
            break;
        case TokenType::LEQUAL:
            if(object1->getType() == ObjectTypes::INT32 && object2->getType() == ObjectTypes::INT32) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<int32_t>() <= object2->getValue<int32_t>());
            }
            else if(object1->getType() == ObjectTypes::STRING && object2->getType() == ObjectTypes::STRING) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<std::string>() <= object2->getValue<std::string>());
            }
            else {
                throw std::runtime_error("<= accepts only string and int32");
            }
            break;
        case TokenType::EQUAL:
            if(object1->getType() == ObjectTypes::INT32 && object2->getType() == ObjectTypes::INT32) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<int32_t>() == object2->getValue<int32_t>());
            }
            else if(object1->getType() == ObjectTypes::STRING && object2->getType() == ObjectTypes::STRING) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<std::string>() == object2->getValue<std::string>());
            }
            else {
                throw std::runtime_error("== accepts only string and int32");
            }
            break;
        case TokenType::GEQUAL:
            if(object1->getType() == ObjectTypes::INT32 && object2->getType() == ObjectTypes::INT32) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<int32_t>() >= object2->getValue<int32_t>());
            }
            else if(object1->getType() == ObjectTypes::STRING && object2->getType() == ObjectTypes::STRING) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<std::string>() >= object2->getValue<std::string>());
            }
            else {
                throw std::runtime_error(">= accepts only string and int32");
            }
            break;
        case TokenType::GREATER:
            if(object1->getType() == ObjectTypes::INT32 && object2->getType() == ObjectTypes::INT32) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<int32_t>() > object2->getValue<int32_t>());
            }
            else if(object1->getType() == ObjectTypes::STRING && object2->getType() == ObjectTypes::STRING) {
                return std::make_shared<Object>(ObjectTypes::BOOL, object1->getValue<std::string>() > object2->getValue<std::string>());
            }
            else {
                throw std::runtime_error("> accepts only string and int32");
            }
            break;
        default:
            throw std::runtime_error("Math operator got not math token");
    }
}
