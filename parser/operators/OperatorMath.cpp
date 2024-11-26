#include "OperatorMath.hpp"

OperatorMath::OperatorMath(const std::shared_ptr<Operator> &operator1, const std::shared_ptr<Operator> &operator2,
                           TokenType tokenType) : m_operator1(operator1), m_operator2(operator2), m_tokenType(tokenType) {}

std::shared_ptr<Object> OperatorMath::getObjectOperator(const std::shared_ptr<Row> & row, const TableMeta & tableMeta) const {
    auto object1 = m_operator1->getObjectOperator(row, tableMeta);
    auto object2 = m_operator2->getObjectOperator(row, tableMeta);
    switch (m_tokenType) {

        case TokenType::IDENTIFIER:
            break;
        case TokenType::COMMA:
            break;
        case TokenType::STRING:
            break;
        case TokenType::BYTES:
            break;
        case TokenType::NUMBER:
            break;
        case TokenType::PLUS:
            break;
        case TokenType::MINUS:
            break;
        case TokenType::STAR:
            break;
        case TokenType::SLASH:
            break;
        case TokenType::MOD:
            break;
        case TokenType::LEN:
            break;
        case TokenType::EQUAL:
            break;
        case TokenType::NEQUAL:
            break;
        case TokenType::LESS:
            break;
        case TokenType::GREATER:
            break;
        case TokenType::LEQUAL:
            break;
        case TokenType::GEQUAL:
            break;
        case TokenType::AND:
            break;
        case TokenType::OR:
            break;
        case TokenType::NOT:
            break;
        case TokenType::LPAREN:
            break;
        case TokenType::RPAREN:
            break;
        case TokenType::XOR:
            break;
        case TokenType::TRUE:
            break;
        case TokenType::FALSE:
            break;
        case TokenType::SQL_SELECT:
            break;
        case TokenType::SQL_FROM:
            break;
        case TokenType::SQL_WHERE:
            break;
        case TokenType::SQL_INSERT:
            break;
        case TokenType::SQL_TO:
            break;
        case TokenType::SQL_DELETE:
            break;
        case TokenType::SQL_CREATE:
            break;
        case TokenType::SQL_JOIN:
            break;
        case TokenType::SQL_ON:
            break;
        case TokenType::SQL_UPDATE:
            break;
        case TokenType::SQL_TABLE:
            break;
        case TokenType::SQL_SET:
            break;
        case TokenType::END:
            break;
    }
    return object1;
}

ObjectTypes OperatorMath::getTypeOperator(const TableMeta &) const {
    return ObjectTypes::BYTES;
}
