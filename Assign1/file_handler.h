#ifndef FILE_HANDLER
#define FILE_HANDLER

#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include <fstream>

/*
    Name        : Sri Satya Sai Immani
    Case ID     : SXI219
    File Name   : file_handler.h
    Date Created: 2024-09-15
    Description : 
        This class helps us to handle file operations in the main file.
*/

using namespace std;
class FileHandler {
    private:

    string _filename;
    int _lines;
    vector<string> _ip_addresses;


    public:

    FileHandler(string filename){
        _filename = filename;

        ifstream input_file;
        input_file.open(_filename);
        
        if(input_file.fail()){
        cout << "Error opening the file " << _filename << endl;
        exit(1);
        }

        stringstream buffer;
        buffer << input_file.rdbuf();

        string token;

        while(getline(buffer,token)){
            _ip_addresses.push_back(token);
        }

        _lines = _ip_addresses.size();
        input_file.close();
    }

    int getNumberOfLines(){
        return _lines;
    }

    vector<string> getIpAddresses(){
        return _ip_addresses;
    }




    
};

#endif