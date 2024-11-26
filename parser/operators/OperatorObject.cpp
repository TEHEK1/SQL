#include "OperatorObject.hpp"

OperatorObject::OperatorObject(const std::shared_ptr<Object> & object) : m_object(object) {}

std::shared_ptr<Object> OperatorObject::getObjectOperator(const std::shared_ptr<Row> &, const TableMeta &) const {
    return m_object;
}

ObjectTypes OperatorObject::getTypeOperator(const TableMeta &) const {
    return m_object->getType();
}
