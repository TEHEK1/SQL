#pragma once
#include "Table.hpp"

class TableFactory {
public:
    std::shared_ptr<Table> filter_equal(const std::string&, const std::shared_ptr<Object>&, const std::shared_ptr<Table>&);
    std::shared_ptr<Table> filter_less(const std::string&, const std::shared_ptr<Object>&, const std::shared_ptr<Table>&);
    std::shared_ptr<Table> filter_greater(const std::string&, const std::shared_ptr<Object>&, const std::shared_ptr<Table>&);
    std::shared_ptr<Table> filter_range(const std::string&, const std::shared_ptr<Object>&, const std::shared_ptr<Table>&);
};
