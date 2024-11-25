#include "InsertToUpdateList.hpp"
#include "TableFactory.hpp"

InsertToUpdateList::InsertToUpdateList(const InsertUpdateList & updateEqualList,
                                       const std::shared_ptr<Relation> & relation) :
                                       m_updateEqualList(updateEqualList), m_relation(relation) {}

bool InsertToUpdateList::execute(const std::shared_ptr<DataBase> & dataBase) const {
    auto table = m_relation->execute(dataBase);
    auto tableMeta = table->getTableMeta();
    TableFactory::InsertOperatorList operatorList(tableMeta.size());
    for(const auto& [columnName, operatorResult] : m_updateEqualList) {
        operatorResult->execute(std::shared_ptr<Row>(), TableMeta());
        operatorList[tableMeta.getByName(columnName)->getRealColumnNum()] = operatorResult;
    }
    return TableFactory::insertColumn(operatorList, table);
}
