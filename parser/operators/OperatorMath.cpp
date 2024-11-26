#include "OperatorMath.hpp"

OperatorMath::OperatorMath(const std::shared_ptr<Operator> &operator1, const std::shared_ptr<Operator> &operator2,
                           TokenType tokenType) : m_operator1(operator1), m_operator2(operator2), m_tokenType(tokenType) {}

std::shared_ptr<Object> OperatorMath::getObjectOperator(const std::shared_ptr<Row> & row, const TableMeta & tableMeta) const {
    auto object1 = m_operator1->getObjectOperator(row, tableMeta);
    auto object2 = m_operator2->getObjectOperator(row, tableMeta);
    switch (m_tokenType) {
        case TokenType::PLUS:
            if(object1->getType() == ObjectTypes::INT32 && object2->getType() == ObjectTypes::INT32) {
                return std::make_shared<Object>(ObjectTypes::INT32, object1->getValue<int32_t>() + object2->getValue<int32_t>());
            }
            else if(object1->getType() == ObjectTypes::STRING && object2->getType() == ObjectTypes::STRING) {
                return std::make_shared<Object>(ObjectTypes::STRING, object1->getValue<std::string>() + object2->getValue<std::string>());
            }
            else {
                throw std::runtime_error("+ accepts only string and int32");
            }
            break;
        case TokenType::MINUS:
            if(object1->getType() == ObjectTypes::INT32 && object2->getType() == ObjectTypes::INT32) {
                return std::make_shared<Object>(ObjectTypes::INT32, object1->getValue<int32_t>() - object2->getValue<int32_t>());
            }
            else {
                throw std::runtime_error("- accepts only int32");
            }
            break;
        case TokenType::STAR:
            if(object1->getType() == ObjectTypes::INT32 && object2->getType() == ObjectTypes::INT32) {
                return std::make_shared<Object>(ObjectTypes::INT32, object1->getValue<int32_t>() * object2->getValue<int32_t>());
            }
            else {
                throw std::runtime_error("* accepts only int32");
            }
            break;
        case TokenType::SLASH:
            if(object1->getType() == ObjectTypes::INT32 && object2->getType() == ObjectTypes::INT32) {
                if(object2->getValue<int32_t>() == 0) {
                    throw std::runtime_error("/ accepts only not null right operand");
                }
                return std::make_shared<Object>(ObjectTypes::INT32, object1->getValue<int32_t>() / object2->getValue<int32_t>());
            }
            else {
                throw std::runtime_error("/ accepts only int32");
            }
            break;
        case TokenType::MOD:
            if(object1->getType() == ObjectTypes::INT32 && object2->getType() == ObjectTypes::INT32) {
                if(object2->getValue<int32_t>() == 0) {
                    throw std::runtime_error("% accepts only not null right operand");
                }
                return std::make_shared<Object>(ObjectTypes::INT32, object1->getValue<int32_t>() % object2->getValue<int32_t>());
            }
            else {
                throw std::runtime_error("% accepts only int32");
            }
            break;
        default:
            throw std::runtime_error("Math operator got not math token");
    }
}

ObjectTypes OperatorMath::getTypeOperator(const TableMeta &) const {
    return ObjectTypes::BYTES;
}
