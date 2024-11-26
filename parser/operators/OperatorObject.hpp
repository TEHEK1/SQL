#pragma once
#include <memory>
#include "Operator.hpp"
class OperatorObject : public Operator {
public:
    explicit OperatorObject(const std::shared_ptr<Object>&);
    std::shared_ptr<Object> getObjectOperator(const std::shared_ptr<Row>&, const TableMeta&) const override;
    ~OperatorObject() override = default;
private:
    std::shared_ptr<Object> m_object;
};
