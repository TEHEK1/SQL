#pragma once
#include <vector>
#include "InsertTo.hpp"
#include <UpdateEqualList.hpp>

class InsertToUpdateList : public InsertTo {
public:
    typedef std::vector<std::pair<std::string, std::shared_ptr<Operator> > > InsertUpdateList;
    InsertToUpdateList(const InsertUpdateList&, const std::shared_ptr<Relation>&);
    bool execute(const std::shared_ptr<DataBase> &) const override;
private:
    InsertUpdateList m_updateEqualList;
    std::shared_ptr<Relation> m_relation;
};
