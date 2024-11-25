#pragma once
#include "ColumnMeta.hpp"
class TableMeta {
public:
    std::shared_ptr<ColumnMeta> getByName() const;
    std::shared_ptr<ColumnMeta> getByNumber() const;
    bool setByName(const std::string&, const std::shared_ptr<ColumnMeta>&);
    size_t size() const;
    std::unordered_map<std::string, std::shared_ptr<ColumnMeta> > getColumnMetas() const;
private:
    std::unordered_map<std::string, long long > m_stringColumnMetas;
    std::unordered_map<long long, std::shared_ptr<ColumnMeta> > m_longColumnMetas;
};
