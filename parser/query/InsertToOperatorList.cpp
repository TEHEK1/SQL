#include "InsertToOperatorList.hpp"

InsertToOperatorList::InsertToOperatorList(const TableFactory::InsertOperatorList & operatorList,
                                           const std::shared_ptr<Relation> & relation)
                                       : m_operatorList(operatorList), m_relation(relation) {}

bool InsertToOperatorList::executeQuery(const std::shared_ptr<DataBase> & dataBase) const {
    auto table = m_relation->getTableRelation(dataBase);
    return TableFactory::insertRow(m_operatorList, m_relation->getTableRelation(dataBase));

}
