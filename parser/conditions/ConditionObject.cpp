#include "ConditionObject.hpp"

ConditionObject::ConditionObject(const std::shared_ptr<Object> & object) : m_object(object) {
    try {
        m_object->getValue<bool>();
    }
    catch (const std::exception& ) {
        throw std::runtime_error("ConditionObject: object must be bool");
    }
}

std::shared_ptr<Table> ConditionObject::getTableCondition(const std::shared_ptr<Table> & table) const {
    if(m_object->getValue<bool>()) {
        return table;
    }
    else {
        return std::make_shared<Table>(table->getTableMeta());
    }
}

std::shared_ptr<Object> ConditionObject::getObjectOperator(const std::shared_ptr<Row> &, const TableMeta &) const {
    return m_object;
}

