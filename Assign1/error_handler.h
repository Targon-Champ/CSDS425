#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <iostream>
#include <string>

/*
    Name        : Sri Satya Sai Immani
    Case ID     : SXI219
    File Name   : error_handler.h
    Date Created: 2024-09-11
    Description : 
        This class helps us to handle errors in the main file.
*/

using namespace std;

class ErrorHandler{


    public:
    ErrorHandler(){}
    void unknownError(const string& command){
            cerr << command << " is an unknown command." << endl;
            cerr << "-s is for summary mode" << endl;
            cerr << "-l is for list mode" << endl;

            cerr << "Example of a valid command: ./proj1 -s -f test-file-1.txt" << endl;
            exit(1);
        }
    void fileNameMissing(){
            cerr << "Error: file name is missing after -f" << endl;

            exit(1);
        }

    void invalidSampleFile(const string& fileName){
        cerr << "Error: Invalid sample file " << fileName << endl;
        cerr << "Please provide a valid sample file" << endl;

        exit(1);}

    void multipleModes(){
        cerr << "Error: Only one mode (-s or -l) can be specified." << endl;
        cerr << "Example of a valid command: ./proj1 -s -f test-file-1.txt" << endl;

        exit(1);
    }

    void noneMode(){
        cerr << "Error: No mode (-s or -l) specified." << endl;
        cerr << "Example of a valid command: ./proj1 -s -f test-file-1.txt" << endl;

        exit(1);
    }

};

#endif