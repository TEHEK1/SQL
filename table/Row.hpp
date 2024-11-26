#pragma once

#include <vector>
#include "Object.hpp"
#include <memory>

class Row {
    public:
        Row(std::vector<std::shared_ptr<Object>> fields) : fields(fields) {};
        std::vector<std::shared_ptr<Object>> getFields() const;
        std::shared_ptr<Object> getField(long long index);
    private:
        std::vector<std::shared_ptr<Object>> fields;
};