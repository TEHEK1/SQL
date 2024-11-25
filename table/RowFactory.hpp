#pragma once
#include <memory>
#include "Row.hpp"

class RowFactory {
public:
    static std::shared_ptr<Row> concatenateRow(const std::shared_ptr<Row>&, const std::shared_ptr<Row>&);
};
