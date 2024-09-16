#ifndef LIST_MODE
#define LIST_MODE

#include <iostream>
#include "mode.h"
#include "ip_validator.h"
#include <unordered_map>

using namespace std;

/*
    Name        : Sri Satya Sai Immani
    Case ID     : SXI219
    File Name   : list_mode.h
    Date Created: 2024-09-15
    Description : 
        This class extends Mode, helps us to handle List mode.
*/


class listMode : public Mode{
    private:
        IPValidator _ip_validator;
        unordered_map<string, string> _validated_ip;

    public:

        void validateIP(vector<string> ips) override{
            for(int i = 0; i < ips.size();i++){
                if(_ip_validator.isValidIP(ips[i])){
                    _validated_ip[ips[i]] = "+";
                } else {
                    _validated_ip[ips[i]] = "-";
                }
            }
        }

        void getResult(vector<string> ips) override{

            for(int i = 0; i <ips.size();i++){
                cout << ips[i] << " " << _validated_ip[ips[i]] << endl;
            }
            
        }




};

#endif