#include <iostream>
#include <string>

using namespace std;

class ErrorHandler{
    public:
    ErrorHandler(){}
        void unknownError(const string& command){
            cerr << command << " is an unknown command." << endl;
            cerr << "-s if for summary mode" << endl;
            cerr << "-l is for list mode" << endl;

            cerr << "Example of a valid command: ./proj1 -s -f test-file-1.txt" << endl;
            exit(1);
            }
};