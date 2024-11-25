#include "SFW.hpp"
SFW::SFW(const std::shared_ptr<SeList> & seList,
        const std::shared_ptr<Relation> & relation,
        const std::shared_ptr<Condition> & condition) : m_seList(seList), m_relation(relation), m_condition(condition){}

std::shared_ptr<Table> SFW::execute(const std::shared_ptr<DataBase> & dataBase) const {
    m_seList->execute(m_condition->execute(m_relation->execute(dataBase)));
}