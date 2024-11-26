#pragma once
#include <string>
#include "Operator.hpp"
class OperatorIdentifier : public Operator {
public:
    OperatorIdentifier(const std::string&);
    std::shared_ptr<Object> getObjectOperator(const std::shared_ptr<Row>&, const TableMeta&) const override;
    ObjectTypes getTypeOperator(const TableMeta &) const override;
    ~OperatorIdentifier() override = default;
private:
    std::string m_columnName;
};
