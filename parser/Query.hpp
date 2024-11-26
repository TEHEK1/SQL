#pragma once
#include <memory>
#include "DataBase.hpp"

class Query {
public:
    virtual bool executeQuery (const std::shared_ptr<DataBase>&) const = 0;
    virtual ~Query() = default; // TODO: override destructors
};
