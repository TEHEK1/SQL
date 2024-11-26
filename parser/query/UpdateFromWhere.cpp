#include "TableFactory.hpp"
#include "UpdateFromWhere.hpp"

UpdateFromWhere::UpdateFromWhere(const UpdateList & updateList,
                                 const std::shared_ptr<Relation> & relation,
                                 const std::shared_ptr<Condition> & condition) :
                                 m_updateList(updateList), m_relation(relation), m_condition(condition) {}

bool UpdateFromWhere::executeQuery(const std::shared_ptr<DataBase> & dataBase) const {
    auto table = m_condition->getTableCondition(m_relation->getTableRelation(dataBase));
    auto tableMeta = table->getTableMeta();
    return TableFactory::updateByUpdateList(table, tableMeta, m_updateList);
}
