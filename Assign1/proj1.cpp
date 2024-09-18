#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include "error_handler.h"
#include "arg_handler.h"
#include "ip_validator.h"
#include "file_handler.h"
#include "summary_mode.h"
#include "list_mode.h"
/*
    Name        : Sri Satya Sai Immani
    Case ID     : SXI219
    File Name   : proj1.cpp
    Date Created: 2024-09-11
    Description : 
        This program runs based on the command line arguements on summary mode or list mode. If any invalid command is given then it will 
        generate a valid error message and exit program.
*/


// Main function
using namespace std;

int main(int argc, char* argv[]){

    vector<string> args(argv+1,argv+argc);
    ErrorHandler error_handler;
    ArgHandler arg_handler(args);
    IPValidator ip_validator;
    



    arg_handler.isValidCommand(args);

    bool is_summary = arg_handler.getSummaryMode();
    bool is_list = arg_handler.getListMode();
    string file_name = arg_handler.getFileName();

    FileHandler file_handler(file_name);

    vector<string> ip_addresses= file_handler.getIpAddresses();

    if (is_summary){
        summaryMode mode;
        mode.validateIP(ip_addresses);
        mode.getResult(ip_addresses);
    }

    if (is_list){
        listMode mode;
        mode.validateIP(ip_addresses);
        mode.getResult(ip_addresses);

    }



    return 0;
}