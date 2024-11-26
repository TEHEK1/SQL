#include "TableFactory.hpp"
bool TableFactory::insertRow(InsertOperatorList insertOperatorList, const std::shared_ptr<Table> & table) {
    auto tableMeta = table->getTableMeta();
    std::vector<std::shared_ptr<Object> > objects;
    for(long long columnNum = 0; columnNum < tableMeta.size(); columnNum ++) {
        auto column = tableMeta.getByNumber(columnNum);
        auto columnIterator = insertOperatorList.find(columnNum);
        std::shared_ptr<Object> insertObject{};
        if(insertOperatorList.find(columnNum) != insertOperatorList.end()) {
            insertObject = columnIterator->second->getObjectOperator(std::shared_ptr<Row>(), TableMeta());
        }
        else if(column->hasAutoIncrement()) {
            insertObject = column->getNextIncrement();
        }
        else if(column->hasDefaultValue()) {
            insertObject = column->getDefaultValue();
        }
        if(! (insertObject && column->canInsert(insertObject))) {
            return false;
        }
        objects.push_back(insertObject);
    }
    auto insertRow = std::make_shared<Row>(objects);
    table->insertRow(insertRow);
    for(long long columnNum = 0; columnNum < tableMeta.size(); columnNum ++) {
        auto column = tableMeta.getByNumber(columnNum);
        column->updateInsert(objects[columnNum], insertRow);
    }
    return true;
}

bool TableFactory::deleteByCondition(const std::shared_ptr<Table>& table, const std::shared_ptr<Condition>& condition) {
    auto& rows = table->rows ;
    for(auto rowIterator = rows.begin(); rowIterator != rows.end(); ) {
        auto isCondition = condition->getObjectOperator(*rowIterator, table->getTableMeta())->getValue<bool>();
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
    return true;
}