#pragma once
#include "Condition.hpp"
#include "Operator.hpp"
#include "Table.hpp"

class TableFactory {
public:
    static std::shared_ptr<Table> filter_equal(const std::string&, const std::shared_ptr<Object>&, const std::shared_ptr<Table>&);
    static std::shared_ptr<Table> filter_less(const std::string&, const std::shared_ptr<Object>&, const std::shared_ptr<Table>&);
    static std::shared_ptr<Table> filter_greater(const std::string&, const std::shared_ptr<Object>&, const std::shared_ptr<Table>&);
    static std::shared_ptr<Table> filter_range(const std::string&, const std::shared_ptr<Object>&, const std::shared_ptr<Object>&, const std::shared_ptr<Table>&);
    typedef std::unordered_map<long long, std::shared_ptr<Operator> > InsertOperatorList;
    static bool insertRow(InsertOperatorList, const std::shared_ptr<Table> &);
    static bool deleteByCondition(const std::shared_ptr<Table>& table, const std::shared_ptr<Condition>& condition);
};
