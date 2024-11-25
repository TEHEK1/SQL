#pragma once
#include <string>
#include "Operator.hpp"
class OperatorIdentifier : public Operator {
public:
    OperatorIdentifier(const std::string&);
    Object execute(const Row&, const ColumnMeta&) override;
    ~OperatorIdentifier() override = default;
};
