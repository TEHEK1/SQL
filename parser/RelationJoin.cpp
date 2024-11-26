#include "RelationJoin.hpp"

RelationJoin::RelationJoin(const std::shared_ptr<Relation> & relation1, const std::shared_ptr<Relation> & relation2,
                           const std::shared_ptr<JoinEqualList> & joinEqualList):
                           m_relation1(relation1), m_relation2(relation2), m_joinEqualList(joinEqualList) {};

std::shared_ptr<Table> RelationJoin::getTableRelation(const std::shared_ptr<DataBase> & dataBase) const {
    auto table1 = m_relation1->getTableRelation(dataBase);
    auto table2 = m_relation2->getTableRelation(dataBase);
    return m_joinEqualList->execute(m_relation1->getName(), table1, m_relation2->getName(), table2);

}

std::string RelationJoin::getName() const {
    return std::string{};
}