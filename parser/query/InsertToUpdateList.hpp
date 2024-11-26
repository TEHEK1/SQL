#pragma once
#include <vector>
#include "InsertTo.hpp"
#include "UpdateEqualList.hpp"

class InsertToUpdateList : public InsertTo {
public:
    InsertToUpdateList(const UpdateList&, const std::shared_ptr<Relation>&);
    bool executeQuery(const std::shared_ptr<DataBase> &) const override;
    ~InsertToUpdateList() override =default;
private:
    UpdateList m_updateList;
    std::shared_ptr<Relation> m_relation;
};
