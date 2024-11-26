#include "DeleteFrom.hpp"
#include "TableFactory.hpp"
DeleteFrom::DeleteFrom(const std::shared_ptr<Relation> & relation,
                       const std::shared_ptr<Condition> & condition) : m_relation(relation), m_condition(condition) {}

bool DeleteFrom::executeQuery(const std::shared_ptr<DataBase> & database) const {
    auto table = m_relation->getTableRelation(database);
    return TableFactory::deleteByCondition(table, m_condition);
}

