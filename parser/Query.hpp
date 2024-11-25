#pragma once

class Query {
public:
    bool execute () const;
    virtual ~Query();
};
