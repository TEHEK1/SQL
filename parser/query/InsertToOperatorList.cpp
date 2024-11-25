#include "InsertToOperatorList.hpp"

InsertToOperatorList::InsertToOperatorList(const TableFactory::InsertOperatorList & operatorList,
                                           const std::shared_ptr<Relation> & relation)
                                       : m_operatorList(operatorList), m_relation(relation) {}

bool InsertToOperatorList::execute(const std::shared_ptr<DataBase> & dataBase) const {
    auto table = m_relation->execute(dataBase);
    return TableFactory::insertColumn(m_operatorList, m_relation->execute(dataBase));

}
