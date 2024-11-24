#pragma once
#include <string>
#include "Condition.hpp"
#include "Object.hpp"

class ConditionIdentifier : Condition {
public:
    ConditionIdentifier(const std::string&);
    Table execute(const Table &) override;
    ~ConditionIdentifier() override = default;
};
