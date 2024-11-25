#pragma once
#include "Condition.hpp"
#include "Object.hpp"

class ConditionObject : Condition {
public:
    ConditionObject(const Object&);
    std::shared_ptr<Table> execute(const Table &) override;
    ~ConditionObject() override = default;
};
