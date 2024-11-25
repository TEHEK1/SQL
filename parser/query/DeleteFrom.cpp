#include "DeleteFrom.hpp"

DeleteFrom::DeleteFrom(const std::shared_ptr<Relation> & relation,
                       const std::shared_ptr<Condition> & condition) : m_relation(relation), m_condition(condition) {}

bool DeleteFrom::execute(const std::shared_ptr<DataBase> & database) const { //TODO: move to TableFactory
    auto table = m_relation->execute(database);
    auto& rows = table->rows ;
    for(auto rowIterator = rows.begin(); rowIterator != rows.end(); ) {
        auto isCondition = m_condition->execute(*rowIterator, table->getTableMeta())->getValue<bool>();
        bool canBeDeleted = true;
        for(const auto& [columnNum, columnMeta] : table->getTableMeta().getLongColumnMetas()) {
            canBeDeleted = canBeDeleted && columnMeta->canDelete((*rowIterator)->getField(columnNum));
        }
        if(!canBeDeleted) {
            return false; // TODO:Here can be exception
        }
        if(isCondition && canBeDeleted) {
            for(const auto& [columnNum, columnMeta] : table->getTableMeta().getLongColumnMetas()) {
                columnMeta->updateDelete((*rowIterator)->getField(columnNum));
            }
            rowIterator = rows.erase(rowIterator);
        }
    }
}

