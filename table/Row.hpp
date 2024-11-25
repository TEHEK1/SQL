#pragma once

#include <vector>
#include "Object.hpp"

class Row {
    public:
        Row(std::vector<std::shared_ptr<Object>> fields) : fields(fields) {};
        
        std::shared_ptr<Object> getField(long long index);
    private:
        std::vector<std::shared_ptr<Object>> fields;
};