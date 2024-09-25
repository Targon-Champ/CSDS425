#ifndef SUMMARY_MODE
#define SUMMARY_MODE

#include <iostream>
#include "mode.h"
#include "ip_validator.h"


using namespace std;

/*
    Name        : Sri Satya Sai Immani
    Case ID     : SXI219
    File Name   : summary_mode.h
    Date Created: 2024-09-15
    Description : 
        This class extends Mode, helps us to handle Summary mode.
*/


class summaryMode : public Mode{
    private:
        
        IPValidator _ip_validator;
        int _valid;
        int _invalid;


    public:

        void validateIP(vector<string> ips) override{

            
            for(size_t i=0; i<ips.size(); i++){
                if(_ip_validator.isValidIP(ips[i])){
                    _valid += 1;
                } else {
                    _invalid += 1;
                }
            }
        }

        void getResult(vector<string> ips) override{

            cout << "LINES: " << ips.size() << endl;
            cout << "VALID: " << _valid << endl;
            cout << "INVALID: " << _invalid << endl;
            
        }




};

#endif