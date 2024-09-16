#ifndef MODE_H
#define MODE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward Declaration

/*
    Name        : Sri Satya Sai Immani
    Case ID     : SXI219
    File Name   : mode.h
    Date Created: 2024-09-15
    Description : 
        This interface helps us to handle different modes in future which enables scalability.
*/

class Mode{
    public:
        virtual void validateIP(vector<string> ips){};
        virtual void getResult(vector<string> ips){};

    virtual ~Mode() {}
};

#endif