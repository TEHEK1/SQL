#pragma once
#include <string>
#include "Operator.hpp"
class OperatorIdentifier : Operator {
    OperatorIdentifier(const std::string&);
    Object execute(const Row&, const ColumnMeta&) override;
    ~OperatorIdentifier() override = default;
};
