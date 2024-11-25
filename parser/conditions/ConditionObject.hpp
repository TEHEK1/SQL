#pragma once
#include "Condition.hpp"
#include "Object.hpp"

class ConditionObject : public Condition {
public:
    ConditionObject(const std::shared_ptr<Object>&);
    std::shared_ptr<Table> execute (const std::shared_ptr<Table> &) const override;
    ~ConditionObject() override = default;
private:
    std::shared_ptr<Object> m_object;
};
