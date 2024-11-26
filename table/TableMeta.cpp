#include "TableMeta.hpp"
#include <unordered_map>

 TableMeta::TableMeta(std::unordered_map<std::string, long long > & m_stringToLongColumnMetas, 
            std::unordered_map<std::string, std::shared_ptr<ColumnMeta> > & m_stringColumnMetas, 
                std::unordered_map<long long, std::shared_ptr<ColumnMeta> > & m_longColumnMetas)
                    :   m_stringToLongColumnMetas(m_stringToLongColumnMetas),
                            m_stringColumnMetas(m_stringColumnMetas),
                                m_longColumnMetas(m_longColumnMetas) {}

TableMeta::TableMeta(const TableMeta &other) : m_stringToLongColumnMetas(other.m_stringToLongColumnMetas),
                            m_stringColumnMetas(other.m_stringColumnMetas),
                                m_longColumnMetas(other.m_longColumnMetas) {}
std::shared_ptr<ColumnMeta> TableMeta::getByName(const std::string& columnName) const {
    auto columnIndex = m_stringToLongColumnMetas.find(columnName);
    if(columnIndex == m_stringToLongColumnMetas.end()) {
        throw std::runtime_error("non-existent table row");
    }
    return getByNumber(columnIndex -> second);
}

std::shared_ptr<ColumnMeta> TableMeta::getByNumber(long long columnIndex) const {
    auto tableMeta = m_longColumnMetas.find(columnIndex);
    if(tableMeta == m_longColumnMetas.end()) {
        throw std::runtime_error("non-existent table row");
    } 
    return tableMeta -> second;
}

bool TableMeta::setByName(const std::string& name, const std::shared_ptr<ColumnMeta>& inforrmation) {
    m_stringColumnMetas[name] = inforrmation;
    m_longColumnMetas[inforrmation -> getRealColumnNum()] = inforrmation;
    m_stringToLongColumnMetas[name] = inforrmation -> getRealColumnNum();
    return true;
}

size_t TableMeta::size() const {
    return m_longColumnMetas.size();
}

std::unordered_map<std::string, std::shared_ptr<ColumnMeta> > TableMeta::getNameColumnMetas() const {
    return m_stringColumnMetas;
}

std::unordered_map<long long, std::shared_ptr<ColumnMeta> > TableMeta::getLongColumnMetas() const {
    return m_longColumnMetas;
}
