#include "TableFactory.hpp"
#include "RowFactory.hpp"
#include "ObjectFactory.hpp"

std::shared_ptr<Table> TableFactory::joinTables(const std::shared_ptr<Table>& table1,  const std::string& tableName1,
                                                const std::shared_ptr<Table>& table2,  const std::string& tableName2,
                                                const std::vector<std::shared_ptr<JoinEqual>>& joinEquals) {
    TableMeta resultTableMeta;
    {
        size_t offset = 0;
        for(const auto& [tableMeta, tableName]:{std::pair{table1->getTableMeta(), tableName1}, std::pair{table2->getTableMeta(), tableName2}}){
            for(const auto& [name, columnMeta] : tableMeta.getNameColumnMetas()) {
                auto realColumnName = tableName;
                realColumnName += ".";
                realColumnName += name;
                resultTableMeta.setByName(realColumnName, std::make_shared<ColumnMeta>(*columnMeta, columnMeta->getRealColumnNum() + offset));
            }
            offset += tableMeta.size();
        }
    }
    auto result = std::make_shared<Table>(resultTableMeta);
    auto joinEqual = joinEquals[0];
    for(const auto& row1:table1->getRows()) {
        auto filtered = joinEqual->execute(row1, table1->getTableMeta(), table2);
        for(const auto& row2:filtered->getRows()) {
            auto current_row = RowFactory::concatenateRow(row1, row2);
            result->insertRow(current_row);
        }
    }
    return result;
}

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
bool TableFactory::updateByUpdateList(const std::shared_ptr<Table>& table, TableMeta& tableMeta, const UpdateList& updateList) {
    for( const auto& row : table->getRows()) {
        for(const auto& [columnName, operatorValue] : updateList) {
            auto columnMeta = tableMeta.getByName(columnName);
            if (!columnMeta->canUpdate(row->getField(columnMeta->getRealColumnNum()), operatorValue->getObjectOperator(row, tableMeta))) {
                return false;
            }
        }
        for(const auto& [columnName, operatorValue] : updateList) {
            auto columnMeta = tableMeta.getByName(columnName);
            columnMeta->updateUpdate(row->getField(columnMeta->getRealColumnNum()), operatorValue->getObjectOperator(row, tableMeta), row);
            row->fields[columnMeta->getRealColumnNum()] = operatorValue->getObjectOperator(row, tableMeta);
        }
    }
    return true;
}

std::shared_ptr<Table> TableFactory::filter_equal(const std::string& name,
        const std::shared_ptr<Object>& equal_object, const std::shared_ptr<Table>& table) {
    
    auto tableMeta = table->getTableMeta();

    std::shared_ptr<Table> resultTableMeta = std::make_shared<Table>(table -> getTableMeta());
    for(const auto& row:table -> getRows()) {
        std::shared_ptr<Object> v = ObjectFactory::getObjectByColumnName(name, row, table -> getTableMeta());
        if(v == equal_object) {
            resultTableMeta -> insertRow(row);
            for(long long columnNum = 0; columnNum < tableMeta.size(); columnNum ++) {
                auto column = tableMeta.getByNumber(columnNum);
                column->updateInsert(row -> getField(columnNum), row);
            }
        }
    }
    return resultTableMeta;
}

std::shared_ptr<Table> TableFactory::filter_less(const std::string& name, 
    const std::shared_ptr<Object>& equal_object, const std::shared_ptr<Table>& table) {
    
    auto tableMeta = table->getTableMeta();

    std::shared_ptr<Table> resultTableMeta = std::make_shared<Table>(table -> getTableMeta());
    for(const auto& row:table -> getRows()) {
        std::shared_ptr<Object> v = ObjectFactory::getObjectByColumnName(name, row, table -> getTableMeta());
        if(v < equal_object) {
            resultTableMeta -> insertRow(row);
            for(long long columnNum = 0; columnNum < tableMeta.size(); columnNum ++) {
                auto column = tableMeta.getByNumber(columnNum);
                column->updateInsert(row -> getField(columnNum), row);
            }
        }
    }
    return resultTableMeta;
    
}

std::shared_ptr<Table> TableFactory::filter_greater(const std::string& name, const std::shared_ptr<Object>& equal_object, const std::shared_ptr<Table>& table) {

    auto tableMeta = table->getTableMeta();

    std::shared_ptr<Table> resultTableMeta = std::make_shared<Table>(table -> getTableMeta());
    for(const auto& row:table -> getRows()) {
        std::shared_ptr<Object> v = ObjectFactory::getObjectByColumnName(name, row, table -> getTableMeta());
        if(v > equal_object) {
            resultTableMeta -> insertRow(row);
            for(long long columnNum = 0; columnNum < tableMeta.size(); columnNum ++) {
                auto column = tableMeta.getByNumber(columnNum);
                column->updateInsert(row -> getField(columnNum), row);
            }
        }
    }
    return resultTableMeta;
}

std::shared_ptr<Table> TableFactory::filter_range(const std::string& name, const std::shared_ptr<Object>& less, 
    const std::shared_ptr<Object>& greater, const std::shared_ptr<Table>& table) {

    auto tableMeta = table->getTableMeta();
    
    std::shared_ptr<Table> resultTableMeta = std::make_shared<Table>(table -> getTableMeta());
    for(const auto& row:table -> getRows()) {
        std::shared_ptr<Object> v = ObjectFactory::getObjectByColumnName(name, row, table -> getTableMeta());
        if(v >= less && v <= greater) {
            resultTableMeta -> insertRow(row);
            for(long long columnNum = 0; columnNum < tableMeta.size(); columnNum ++) {
                auto column = tableMeta.getByNumber(columnNum);
                column->updateInsert(row -> getField(columnNum), row);
            }
        }
    }
    return resultTableMeta;
}


