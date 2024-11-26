#include "InsertToUpdateList.hpp"
#include "TableFactory.hpp"

InsertToUpdateList::InsertToUpdateList(const UpdateList & updateList,
                                       const std::shared_ptr<Relation> & relation) :
                                       m_updateList(updateList), m_relation(relation) {}

bool InsertToUpdateList::executeQuery(const std::shared_ptr<DataBase> & dataBase) const {
    auto table = m_relation->getTableRelation(dataBase);
    auto tableMeta = table->getTableMeta();
    TableFactory::InsertOperatorList operatorList(tableMeta.size());
    for(const auto& [columnName, operatorResult] : m_updateList) {
        operatorResult->getObjectOperator(std::shared_ptr<Row>(), TableMeta());
        operatorList[tableMeta.getByName(columnName)->getRealColumnNum()] = operatorResult;
    }
    return TableFactory::insertRow(operatorList, table);
}
