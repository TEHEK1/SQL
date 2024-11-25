#include "RelationJoin.hpp"

RelationJoin::RelationJoin(const std::shared_ptr<Relation> & relation1, const std::shared_ptr<Relation> & relation2,
                           const std::shared_ptr<JoinEqualList> & joinEqualList):
                           m_relation1(relation1), m_relation2(relation2), m_joinEqualList(joinEqualList) {};

std::shared_ptr<Table> RelationJoin::execute(const std::shared_ptr<DataBase> & dataBase) {
    auto table1 = m_relation1->execute(dataBase);
    auto table2 = m_relation2->execute(dataBase);
    auto resultTable = std::make_shared<Table>();
    for(const auto& row1:table1->getRows()) {
        
    }
}