#pragma once
#include <memory>
#include "DataBase.hpp"

class Query {
public:
    virtual bool execute (const std::shared_ptr<DataBase>&) const = 0;
    virtual ~Query();
};
