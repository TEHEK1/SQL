#pragma once
#include <string>
#include <vector>
#include "UpdateEqualList.hpp"

class InsertList { // Можно отнаследовать два разных, но посыл такой
    InsertList(std::vector<Object>&);
    InsertList(const UpdateList&);
    bool execute(Table&);
};
