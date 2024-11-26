#pragma once
#include <string>
#include <vector>
#include "Operator.hpp"
#include "Table.hpp"
typedef std::vector<std::pair<std::string, std::shared_ptr<Operator> > > UpdateList;