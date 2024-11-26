#pragma once
#include "ColumnMeta.hpp"
#include <unordered_map>

class TableMeta {
public:
    TableMeta(std::unordered_map<std::string, long long > &, 
        std::unordered_map<std::string, std::shared_ptr<ColumnMeta> > &, 
            std::unordered_map<long long, std::shared_ptr<ColumnMeta> > &);
    
    TableMeta(const TableMeta &other);

    TableMeta() = default;

    std::shared_ptr<ColumnMeta> getByName(const std::string&) const; // 
    std::shared_ptr<ColumnMeta> getByNumber(long long) const;
    bool setByName(const std::string&, const std::shared_ptr<ColumnMeta>&);
    size_t size() const;
    std::unordered_map<std::string, std::shared_ptr<ColumnMeta> > getNameColumnMetas() const;
    std::unordered_map<long long, std::shared_ptr<ColumnMeta> > getLongColumnMetas() const;
private:
    std::unordered_map<std::string, long long > m_stringToLongColumnMetas;
    std::unordered_map<std::string, std::shared_ptr<ColumnMeta> > m_stringColumnMetas;
    std::unordered_map<long long, std::shared_ptr<ColumnMeta> > m_longColumnMetas;
};
