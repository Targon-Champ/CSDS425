#ifndef ARG_HANDLER_H
#define ARG_HANDLER_H
#include <iostream>
#include <string>
#include <vector>
#include "error_handler.h"

/*
    Name        : Sri Satya Sai Immani
    Case ID     : SXI219
    File Name   : arg_handler.h
    Date Created: 2024-09-15
    Description : 
        This class helps us to handle arguement checks and also setting valid modes in the main file.
*/

using namespace std;

class ArgHandler {
    private:
        bool _is_summary;
        bool _is_list;
        string _file_name;
        ErrorHandler _error_handler;
    
    public:


       ArgHandler(vector<string> args){

        _is_summary = find(args.begin(),args.end(),"-s") != args.end();
        _is_list = find(args.begin(),args.end(),"-l") != args.end();
        vector<string>::iterator it = find(args.begin(),args.end(),"-f");

        if (it != args.end()){
            try{
                if (++it == args.end())
                    _error_handler.fileNameMissing();

                _file_name = *it;
                }
            catch (const exception){}
        }

 }

        /*
            isValidCommand searches for any invalid mode arguements and throws an error if there are any. 
            Also validates whether we are running the command in a single mode or multiple modes. 
            If multiple modes are given then this function throws an error message.
        */
        void isValidCommand(vector<string> args){   
            if(_is_list && _is_summary){
                _error_handler.multipleModes();
            }

            if (!_is_list && !_is_summary){
                _error_handler.noneMode();
            }
            string prevArg = "";
            for(int i = 0; i < args.size();i++){
                if(args[i]!="-s" && args[i]!="-l" && args[i]!="-f"){
                    if(prevArg != "-f"){
                        _error_handler.unknownError(args[i]);
                    }
                }
                prevArg = args[i];
            }
        }


        string getFileName(){
            return _file_name;
        }

        bool getSummaryMode(){
            return _is_summary;
        }

        bool getListMode(){
            return _is_list;
        }

};

#endif