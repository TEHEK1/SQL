#include "ConditionObject.hpp"

ConditionObject::ConditionObject(const std::shared_ptr<Object> & object) : m_object(object) {
    try {
        m_object->getValue<bool>();
    }
    catch (const std::exception& ) {
        throw std::runtime_error("ConditionObject: object must be bool");
    }
}

std::shared_ptr<Table> ConditionObject::execute(const std::shared_ptr<Table> & table) const {
    if(m_object->getValue<bool>()) {
        return table;
    }
    else {
        return std::make_shared<Table>(table->getTableMeta());
    }
}

