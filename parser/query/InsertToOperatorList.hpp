#pragma once
#include "TableFactory.hpp"
#include "InsertTo.hpp"

class InsertToOperatorList : public InsertTo {
public:
    InsertToOperatorList(const TableFactory::InsertOperatorList&, const std::shared_ptr<Relation>&);
    bool executeQuery(const std::shared_ptr<DataBase> &) const override;
private:
    TableFactory::InsertOperatorList m_operatorList;
    std::shared_ptr<Relation> m_relation;
};
