#pragma once
#include <memory>
#include "DataBase.hpp"

class Query {
public:
    bool execute (const std::shared_ptr<DataBase>&) const;
    virtual ~Query();
};
