#include "TableFactory.hpp"
bool TableFactory::insertColumn(InsertOperatorList insertOperatorList, const std::shared_ptr<Table> & table) {
    auto tableMeta = table->getTableMeta();
    std::vector<std::shared_ptr<Object> > objects;
    for(long long columnNum = 0; columnNum < tableMeta.size(); columnNum ++) {
        auto column = tableMeta.getByNumber(columnNum);
        auto columnIterator = insertOperatorList.find(columnNum);
        std::shared_ptr<Object> insertObject{};
        if(insertOperatorList.find(columnNum) != insertOperatorList.end()) {
            insertObject = columnIterator->second->execute(std::shared_ptr<Row>(), TableMeta());
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