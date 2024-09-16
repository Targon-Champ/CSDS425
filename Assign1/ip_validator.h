#ifndef IP_VALIDATOR
#define IP_VALIDATOR

#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
    Name        : Sri Satya Sai Immani
    Case ID     : SXI219
    File Name   : ip_validator.h
    Date Created: 2024-09-15
    Description : 
        This class helps us to handle ip validations in the file handling file.
*/

class IPValidator{
    private:

    public:
        IPValidator(){}

        bool isValidIP(string ip){

            regex pattern("^(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\."
                       "(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\."
                       "(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\."
                       "(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])$");
            return regex_match(ip, pattern);
        }


};


#endif