#include <iostream>
#include "SFW.hpp"

SFW::SFW(const std::shared_ptr<SeList> & seList,
        const std::shared_ptr<Relation> & relation,
        const std::shared_ptr<Condition> & condition) : m_seList(seList), m_relation(relation), m_condition(condition){}

std::string SFW::getName() const {
    return {};
}
std::shared_ptr<Table> SFW::getTableRelation(const std::shared_ptr<DataBase> & dataBase) const { // TODO: Расставить const
    return m_seList->getTable(m_condition->getTableCondition(m_relation->getTableRelation(dataBase)));
}

bool SFW::executeQuery(const std::shared_ptr<DataBase> & dataBase) const {
    const auto table = getTableRelation(dataBase);
    for(const auto& row : table->getRows()) {
        for(auto column : row->getFields()) {
            switch (column->getType()) {
                case ObjectTypes::INT32:
                    std::cout << column->getValue<int32_t>() << " ";
                    break;
                case ObjectTypes::BOOL:
                    std::cout << column->getValue<bool>() << " ";
                    break;
                case ObjectTypes::STRING:
                    std::cout << column->getValue<std::string>() << " ";
                    break;
                case ObjectTypes::BYTES:
                    std::cout << column->getValue<std::vector<bool>>()[0] << " ";
                    break;
            }
            std::cout << std::endl;
        }
    }
    std::cout << "---------------------------------------------------------------" << std::endl;


    return true;
}
