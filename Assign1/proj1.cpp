#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<map>
#include<fstream>
#include "error_handler.cpp"

using namespace std;

int main(int argc, char* argv[]){

    vector<string> args(argv,argv+argc);
    ErrorHandler errorHandler;

    bool isSummary;
    bool isList;

    string file_name;

    for (int i=1;i<args.size();i++){

        const string& mode = args[i];
        if (mode == "-s"){
            isSummary = true;
        }
        else if (mode == "-l"){
            isList = true;
        }
        else if (mode == "-f"){
            file_name = args[i+1];
            i+=1;
        }
        else{
            errorHandler.unknownError(mode);
        }
    }

    

    return 0;
}
