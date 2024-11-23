#pragma once
#include <string>
#include <vector>

class Query {
    Query();

};

class Attribute {

};

class Relation {

};

class SeList {
    SeList(const std::vector<Attribute> &attributes);
};

class Condition {

};

class FromList {
    FromList(const std::vector<Relation> &relations);
};

class SFW : Query { //SFW = Select ... from .. where
    SFW(const SeList& se_list, const FromList& from_list, const Condition& condition):Query() {};
};

